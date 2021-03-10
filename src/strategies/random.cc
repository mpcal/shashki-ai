#include <random>
#include "strategies.h"

using namespace std;

namespace shashki {

static random_device r;
static seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
static shared_ptr<mt19937> eng = make_shared<mt19937>(seed);

Move random_strategy(const Slice& bk, const Slice& wt, const bool blacks_turn,
                     const Loc& from) {
  // find all valid moves
  vector<Move> moves;
  if (from == NO_LOC)
    moves = valid_moves(bk, wt, blacks_turn);
  else {
    moves = valid_capturing_moves_from(bk, wt, from);
    // if (!blacks_turn) {
    //   printf("sooooo..: from=%lu #moves=%lu\n", from, moves.size());
    //   print_board(bk, wt, moves);
    //   printf("exit.\n");
    //   exit(1);
    // }
  }

  if (moves.empty()) return NO_MOVE;

  uniform_int_distribution<> uniform(0, moves.size() - 1);
  return moves[uniform(*eng)];
}

}  // namespace shashki
