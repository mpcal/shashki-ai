#include <atomic>
#include <limits>

#include "_board_internal.h"
#include "game.h"
#include "game_history.h"
#include "game_stats.h"
#include "valuation.h"

using namespace std;

namespace shashki {

int vfunc_basic(const Slice &bk, const Slice &wt, const bool,
                const uint_fast8_t) {
  const int n_bk = __builtin_popcount(get_men_32(bk)) +
                   2 * __builtin_popcount(get_kings_32(bk));
  const int n_wt = __builtin_popcount(get_men_32(wt)) +
                   2 * __builtin_popcount(get_kings_32(wt));

  if (n_bk == 0)
    return WHITE_WIN_VALUE;
  else if (n_wt == 0)
    return BLACK_WIN_VALUE;

  return n_bk - n_wt;
}

int vfunc_rollout(const Slice &bk, const Slice &wt, const bool blacks_turn,
                  const uint_fast8_t cur_depth) {
  constexpr uint_fast64_t n_games = 1000;
  GameHistory history;
  GameStats stats;

  // initialize score; 2 points per black win, 1 point for a draw
  int score = -(int)n_games;

  for (uint_fast64_t i = 0; i < n_games; ++i) {
    Slice _bk(bk), _wt(wt);

    const GameStatus &status =
        play_to_end(random_strategy, random_strategy, _bk, _wt, blacks_turn)
            .status;

    // 2 points per black win, 1 point for a draw
    score +=
        2 * (status == GameStatus::BLACK_WINS) + (status == GameStatus::DRAW);
  }

  return score;
}

int vfunc_basic_rollout(const Slice &bk, const Slice &wt,
                        const bool blacks_turn, const uint_fast8_t cur_depth) {
  const int n1 = __builtin_popcount(get_men_32(bk)) +
                 2 * __builtin_popcount(get_kings_32(bk));
  const int n2 = __builtin_popcount(get_men_32(wt)) +
                 2 * __builtin_popcount(get_kings_32(wt));

  constexpr uint_fast64_t n_games = 100;
  GameHistory history;
  GameStats stats;

  // initialize score; 2 points per black win, 1 point for a draw
  int score = -(int)n_games;

  for (uint_fast64_t i = 0; i < n_games; ++i) {
    Slice _bk(bk), _wt(wt);

    const GameStatus &status =
        play_to_end(random_strategy, random_strategy, _bk, _wt, blacks_turn)
            .status;

    // 2 points per black win, 1 point for a draw
    score +=
        2 * (status == GameStatus::BLACK_WINS) + (status == GameStatus::DRAW);
  }

  return n1 - n2 + 3 * ((score > 0) - (score < 0));
}

}  // namespace shashki
