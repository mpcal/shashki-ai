#include <array>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include "board.h"
#include "game.h"
#include "strategies.h"

using namespace std;

namespace shashki {

static constexpr uint_fast32_t MAX_PLIES = 128;
static constexpr uint_fast64_t N_GAMES = 150000;

static random_device r;
static seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
static shared_ptr<mt19937> eng = make_shared<mt19937>(seed);
static uniform_real_distribution<> uniform;

// Accumulator type, see two instances below
//
// bk_acc[bk][wt]: board value if black is up (from black's perspective, higher
// is better)
//
// bk_acc[bk][wt]: dito, if white is up
using Accum = unordered_map<Slice, unordered_map<Slice, int_fast32_t>>;

static void dump_acc_to_libsvm(const Accum& acc, const string& train_file,
                               const string& test_file, int category) {
  const auto format_row = [&category](Slice bk, Slice wt,
                                      const int_fast32_t& val) {
    ostringstream row;
    if (false) {
      const int bk_lo = bk & 0xffffffff;
      const int bk_hi = bk >> 32;
      const int wt_lo = wt & 0xffffffff;
      const int wt_hi = wt >> 32;

      char buf[256];
      sprintf(buf, "%d 1:%d 2:%d 3:%d 4:%d 5:%d", val > 0 ? 1 : 0, bk_lo, bk_hi,
              wt_lo, wt_hi, category);
      row << buf;
    } else {
      row << (val > 0 ? 1 : 0);
      for (int i = 0; i < 64; ++i)
         row << " " << (i + 1) << ":" << GET_64(bk, i);
      for (int i = 64; i < 128; ++i)
         row << " " << (i + 1) << ":" << GET_64(wt, i);
      row << " 129:" << category;
    }

    return row.str();
  };

  const double train_frac = 0.85;

  ofstream ofs_train("train.libsvm", ios_base::app);
  ofstream ofs_test("test.libsvm", ios_base::app);

  for (auto const& [bk, wt_map] : acc)
    for (auto const& [wt, val] : wt_map) {
      if (val == 0) continue;
      ofstream& ofs = uniform(*eng) < train_frac ? ofs_train : ofs_test;
      ofs << format_row(bk, wt, val) << endl;
    }
}

void generate_mc_data() {
  Slice bk_hist[MAX_PLIES], wt_hist[MAX_PLIES];
  bool bk_turn_hist[MAX_PLIES];
  uint_fast32_t ply;
  GameStatus status;
  uint_fast64_t generated = 0;

  Accum bk_acc, wt_acc;

  const Strategy& strat = random_strategy;

  for (uint_fast64_t i = 0; i < N_GAMES; ++i) {
    GameHistory history;  // unused
    Slice bk = 4095UL;
    Slice wt = 4095UL << 20;
    bool blacks_turn = i % 2 == 0;

    for (ply = 0; ply < MAX_PLIES; ++ply) {
      status = play_a_ply(bk, wt, blacks_turn, history, &strat);

      if (status != GameStatus::IN_PROGRESS) break;

      bk_hist[ply] = bk;
      wt_hist[ply] = wt;
      bk_turn_hist[ply] = blacks_turn;

      blacks_turn = !blacks_turn;
    }

    int_fast32_t value = (status == GameStatus::BLACK_WINS) * 1 +
                         (status == GameStatus::WHITE_WINS) * -1;
    for (int j = 0; j < ply; ++j) {
      if (bk_turn_hist[j])
        bk_acc[bk_hist[j]][wt_hist[j]] += value;
      else
        wt_acc[bk_hist[j]][wt_hist[j]] += value;
    }

    generated += ply;
  }

  printf("Generated %lu samples, writing train and test files...\n", generated);
  const string& train_file = "train.libsvm";
  const string& test_file = "test.libsvm";
  remove(train_file.c_str());
  remove(test_file.c_str());
  dump_acc_to_libsvm(bk_acc, train_file, test_file, 1);
  dump_acc_to_libsvm(wt_acc, train_file, test_file, 0);
}

}  // namespace shashki
