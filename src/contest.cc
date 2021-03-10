#include "contest.h"
#include <cstdio>
#include <ctime>
#include "board.h"
#include "game.h"
#include "game_stats.h"

using namespace std;

namespace shashki {

GameStats run_contest(const Strategy& bk_strategy, const Strategy& wt_strategy,
                      const uint_fast64_t n_games) {
  bool blacks_turn = false;

  GameStats stats;
  for (uint_fast64_t i = 0; i < n_games; ++i) {
    // start with initial board
    Slice bk = 4095UL, wt = 4095UL << 20;

    const GameResult& res =
        play_to_end(bk_strategy, wt_strategy, bk, wt, blacks_turn);

    stats.update(res);

    // alternate to average out initial asymmetry effects despite violating the
    // "white begins" rule
    blacks_turn = !blacks_turn;
  }

  return stats;
}

}  // namespace shashki
