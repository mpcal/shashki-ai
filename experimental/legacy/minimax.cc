#include <random>
#include "valuation.h"
#include "strategies.h"

using namespace std;

namespace shashki {

static random_device r;
static seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
static shared_ptr<mt19937> eng = make_shared<mt19937>(seed);

// returns a random int in 0..mx-1
inline uint_fast8_t rand_uint8(const uint_fast8_t& mx) {
  assert(mx > 0);
  return std::uniform_int_distribution<>(0, mx - 1)(*eng);
}

// returns the indices of all elements equal to the maximum value in `v`
static vector<uint_fast8_t> all_max_elements(const vector<int>& v) {
  vector<uint_fast8_t> indices;
  int cur_max = numeric_limits<int>::min();

  assert(v.size() < numeric_limits<uint_fast8_t>::max());
  for (uint_fast8_t i = 0; i < (uint_fast8_t)v.size(); ++i) {
    if (v[i] > cur_max) {
      cur_max = v[i];
      indices.clear();
    }

    if (v[i] == cur_max) indices.push_back(i);
  }

  return indices;
}

// returns the indices of all elements equal to the minimum value in `v`
static vector<uint_fast8_t> all_min_elements(const vector<int>& v) {
  vector<uint_fast8_t> indices;
  int cur_min = numeric_limits<int>::max();

  assert(v.size() < numeric_limits<uint_fast8_t>::max());
  for (uint_fast8_t i = 0; i < (uint_fast8_t)v.size(); ++i) {
    if (v[i] < cur_min) {
      cur_min = v[i];
      indices.clear();
    }

    if (v[i] == cur_min) indices.push_back(i);
  }

  return indices;
}

// returns the optimal score of the current depth
//
// - best_move: output variable for best move
// - _dfs_indent: indentation for output; must be 0 at initial call
static int _dfs(const Slice& bk, const Slice& wt, const bool blacks_turn,
                const uint_fast8_t& depth, const Loc& from, Move& best_move,
                const ValueEstimator& value_estim, int _dfs_indent = 0) {
  string _indent =
      string(_dfs_indent, ' ') + "(d" + std::to_string(depth) + ") ";
  const char* indent = _indent.c_str();

  if (depth == 0) return value_estim(bk, wt, blacks_turn);

  // get all possible moves on the board or return score if no moves left
  vector<Move> moves;
  if (from == NO_LOC) {
    moves = valid_moves(bk, wt, blacks_turn);
    if (moves.size() == 0)  // reached leaf
      return value_estim(bk, wt, blacks_turn);
  } else {
    moves = valid_capturing_moves_from(bk, wt, from);
    if (moves.size() == 0) {
      if (_dfs_indent == 0)
        // no moves during initial call means we're done, no recursion
        return value_estim(bk, wt, blacks_turn);
      else
        return _dfs(bk, wt, !blacks_turn, depth - 1, NO_LOC, best_move,
                    value_estim, _dfs_indent + 4);
    }
  }

  // compute all scores of the options
  vector<int> scores;
  //   scores.reserve(moves.size());
  for (int i = 0; i < (int)moves.size(); ++i) {
    const auto& mv = moves[i];

    Slice _bk(bk), _wt(wt);
    const bool capture = do_move(_bk, _wt, mv);

    // printf("%sBranch: %lu -> %lu (capt: %d, black: %d)\n", indent,
    //   get_from(mv), get_to(mv), capture, blacks_turn);
    int score;
    if (capture) {
      // initiate "capturing recursion": same player, same depth
      score = _dfs(_bk, _wt, blacks_turn, depth, get_to(mv), best_move,
                   value_estim, _dfs_indent + 2);
    } else {
      score = _dfs(_bk, _wt, !blacks_turn, depth - 1, NO_LOC, best_move,
                   value_estim, _dfs_indent + 4);
    }

    scores.push_back(score);
  }
  assert(moves.size() == scores.size());

  // by convention black's the maximizing player
  int ix;
  if (blacks_turn)
    ix = max_element(scores.begin(), scores.end()) - scores.begin();
  else
    ix = min_element(scores.begin(), scores.end()) - scores.begin();

  // printf("%sMoves and scores (blacks_turn=%d):\n", indent, blacks_turn);
  // for (int i = 0; i < (int)scores.size(); ++i)
  //   printf("%s %c%lu -> %lu: score %d\n", indent, ix == i ? '*' : ' ',
  //        get_from(moves[i]), get_to(moves[i]), scores[i]);

  best_move = moves[ix];
  return scores[ix];  // remember the best move at top level
}

Move minimax_strategy(const Slice& bk, const Slice& wt, const bool blacks_turn,
                   const Loc& from, const uint_fast8_t search_depth,
                   const ValueEstimator& value_estim) {
  Move best_move = NO_MOVE;
  _dfs(bk, wt, blacks_turn, search_depth, from, best_move, value_estim);

  return best_move;
}

}  // namespace shashki
