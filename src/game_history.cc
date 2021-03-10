#include "game_history.h"
#include <string>

using namespace std;

namespace shashki {

string to_string(const GameHistory& hist) {
  char buf[256];
  sprintf(buf,
          "GameHistory(moves=%u, r723_cnt=%d, r724_cnt=%d, r725_cnt=%d, "
          "r726_c45=%d, r726_c67=%d, r727_cnt=%d, r728_cnt=%d)",
          (unsigned int)hist.move_cnt, hist.r723_cnt, hist.r724_cnt,
          hist.r725_cnt, hist.r726_c45, hist.r726_c67, hist.r727_cnt,
          hist.r728_cnt);
  return buf;
}

}  // namespace shashki
