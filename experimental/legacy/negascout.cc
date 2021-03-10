/**
 * NegaScout implementaiton for Shashki,
 * https://en.wikipedia.org/wiki/Principal_variation_search
 */

#include <random>
#include "valuation.h"
#include "strategies.h"

using namespace std;

namespace shashki {

// value in 0..48
int eval(const Slice& bk, const Slice& wt) {
  const int n1 = __builtin_popcount(get_men_32(bk)) +
                 2 * __builtin_popcount(get_kings_32(bk));
  const int n2 = __builtin_popcount(get_men_32(wt)) +
                 2 * __builtin_popcount(get_kings_32(wt));

  return n1 - n2 + 24;
}

// color == 1 <=> blacks_turn, color == -1 <=> !blacks_turn
static int _pvs(const Slice& bk, const Slice& wt, const uint_fast8_t& depth,
                const Loc& from, Move& best_move, int alpha, int beta,
                int color, bool top_level = true) {
  if (depth == 0) return color * eval(bk, wt);

  const bool blacks_turn = color == 1;
  assert(blacks_turn || color == -1);

  // get all possible moves on the board or return score if no moves left
  vector<Move> moves;
  if (from == NO_LOC) {
    moves = valid_moves(bk, wt, blacks_turn);
    if (moves.size() == 0)  // reached leaf
      return color * eval(bk, wt);
  } else {
    moves = valid_capturing_moves_from(bk, wt, from);
    if (moves.size() == 0) {
      if (top_level)
        // no moves during initial call means we're done, no recursion
        return color * eval(bk, wt);
      else
        return -_pvs(bk, wt, depth - 1, NO_LOC, best_move, -beta, -alpha,
                     -color, false);
    }
  }

  // compute all scores of the options
  for (int i = 0; i < (int)moves.size(); ++i) {
    const auto& mv = moves[i];

    Slice _bk(bk), _wt(wt);
    const bool capture = do_move(_bk, _wt, mv);

    int score;
    if (i == 0) {
      if (capture)
        // initiate "capturing recursion": same player, same depth
        score = _pvs(_bk, _wt, depth, get_to(mv), best_move, alpha, beta, color,
                     false);
      else
        score = -_pvs(_bk, _wt, depth - 1, NO_LOC, best_move, -beta, -alpha,
                      -color, false);
    } else {
      if (capture)
        // initiate "capturing recursion": same player, same depth
        score = _pvs(_bk, _wt, depth, get_to(mv), best_move, alpha, beta, color,
                     false);
      else {
        score = -_pvs(_bk, _wt, depth - 1, NO_LOC, best_move, -alpha - 1,
                      -alpha, -color, false);

        if (alpha < score && score < beta)
          score = -_pvs(_bk, _wt, depth - 1, NO_LOC, best_move, -beta, -score,
                        -color, false);
      }
    }

    // printf("score: %d\n", score);
    if ((alpha > score || alpha >= beta) && top_level) best_move = mv;

    alpha = max(alpha, score);
    if (alpha >= beta) {
      printf("cutoff set alpha=%d beta=%d depth=%d\n", alpha, beta, depth);
      // throw runtime_error("oh!");
      break;  // beta cut-off
    }
  }

  return alpha;
}

Move pvs_strategy(const Slice& bk, const Slice& wt, const bool blacks_turn,
                  const Loc& from, const uint_fast8_t search_depth) {
  Move best_move = NO_MOVE;
  _pvs(bk, wt, search_depth, from, best_move, numeric_limits<int>::min() + 1000,
       numeric_limits<int>::max() - 1000, blacks_turn ? 1 : -1);

  printf("white's best move:\n");
  printf("  %s\n", to_string(best_move).c_str());

  return best_move;
}

}  // namespace shashki
