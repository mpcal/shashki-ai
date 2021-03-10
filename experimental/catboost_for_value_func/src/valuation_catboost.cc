#include <catboost_model/wrapped_calcer.h>
#include <limits>

#include "_board_internal.h"
#include "game.h"
#include "game_history.h"
#include "game_stats.h"
#include "valuation.h"

using namespace std;

namespace shashki {

extern int realdepth;

static ModelCalcerWrapper calcer("/home/mike/code/shashki/learn_clf/model.bin");
static vector<float> float_features(128);
static vector<string> cat_features(1);

int value_func_4(const Slice &bk, const Slice &wt, bool blacks_turn) {
  return value_func_3(bk, wt, blacks_turn) + value_func_1(bk, wt, blacks_turn);
}

int value_func_catboost(const Slice &bk, const Slice &wt, bool blacks_turn) {
  for (int i = 0; i < 64; ++i) float_features[i] = GET_64(bk, i);
  for (int i = 64; i < 128; ++i) float_features[i] = GET_64(wt, i);
  cat_features[0] = blacks_turn ? "1" : "0";

  // these raw scores are [logits](https://en.wikipedia.org/wiki/Logit),
  // therefore proba = exp(score) / (1 + exp(score))
  const double score = calcer.Calc(float_features, cat_features);
  // const double p = exp(score) / (1 + exp(score));

  // round and bound
  int val = round(1e6 * score);
  val = min(BLACK_WIN_VALUE, max(WHITE_WIN_VALUE, val));

  return val;
}

}  // namespace shashki
