#pragma once

#include "game_stats.h"

namespace shashki {

// runs a contest between two strategies and returns the stats
GameStats run_contest(const Strategy& bk_strategy, const Strategy& wt_strategy,
                      const uint_fast64_t n_games);

}  // namespace shashki
