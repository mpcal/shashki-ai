#include <catboost_model/wrapped_calcer.h>
#include <limits>

#include "_board_internal.h"
#include "game.h"
#include "game_history.h"
#include "game_stats.h"
#include "valuation.h"

using namespace std;

namespace shashki {

int value_func_cmaes(const Slice &bk, const Slice &wt, bool, const double *ws) {
  double dval = 0.;
  for (int i = 0; i < 32; ++i) {
    dval += (GET_64(bk, i) + 1.5 * GET_64(bk, i + 32)) * ws[i];
    dval -= (GET_64(wt, i) + 1.5 * GET_64(wt, i + 32)) * ws[i + 32];
  }

  // round and bound
  int val = round(1e6 * dval);
  val = min(BLACK_WIN_VALUE, max(WHITE_WIN_VALUE, val));

  return val;
}

}  // namespace shashki
