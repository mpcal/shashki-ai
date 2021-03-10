#include "game_stats.h"
#include <cstdio>

using namespace std;

namespace shashki {

string to_string(const GameStats& stats) {
  char buf[256];
  sprintf(buf,
          "GameStats(bk_wins=%4lu, wt_wins=%4lu, draws=%4lu, plies/game=%.1f)",
          stats.bk_wins, stats.wt_wins, stats.draws,
          stats.n_plies / (double)stats.n_games);
  return buf;
}

}  // namespace shashki
