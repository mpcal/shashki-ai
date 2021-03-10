#include <cstdio>
#include <ctime>
#include <functional>
#include <iomanip>
#include "board.h"
#include "contest.h"
#include "game.h"
#include "game_stats.h"
#include "learn_value_func.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundefined-var-template"
#include <libcmaes/cmaes.h>
#pragma clang diagnostic pop

using namespace std;
using namespace libcmaes;

namespace shashki {

static random_device r;
static seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
static mt19937 eng(seed);
static uniform_real_distribution<> uniform;

// dimensionality of optimization problem
static constexpr size_t N_DIM = 64;

// double score = w[0] * bk_m + w[1] * wt_m + w[2] * bk_k + w[3] * wt_k;
// score /= fabs(w[0]) + fabs(w[1]) + fabs(w[2]) + fabs(w[3]);

// int i_score = round(1000 * score);

// return min(BLACK_WIN_VALUE, max(WHITE_WIN_VALUE, i_score));
// }  // namespace shashki

static string stringify(const double* xs) {
  string value;
  char buf[16];
  for (int i = 0; i < N_DIM; ++i) {
    sprintf(buf, "% 10.7f, ", xs[i]);
    value += buf;
  }
  return value.substr(0, value.length() - 3);
}

static string stringify(const vector<double>& xs) {
  return stringify(xs.data());
}

static int ref_vfunc(const Slice& bk, const Slice& wt, bool) {
  // const vector<double> ws{
  //     0.985415, 1.06695, 1.01504, 1.01517,  1.08756,  0.982051, 0.989468,
  //     1.03575,  1.02059, 1.00069, 1.00459,  1.088,    1.08186,  1.0208,
  //     0.937731, 1.0648,  1.02567, 0.995322, 0.969655, 1.14978,  1.10013,
  //     1.08064,  1.02556, 1.07696, 1.00945,  1.00965,  1.04293,  1.04959,
  //     0.980993, 1.12545, 1.09523, 1.00787};

  // const vector<double> ws{
  //     0.573745, 0.898291, 0.910179, 1.56753, 1.39136, 0.976233, 0.954946,
  //     1.19467,  0.962145, 1.45356,  1.26199, 1.87078, 1.35248,  0.941715,
  //     0.356096, 0.28763,  0.896598, 1.30471, 1.12742, 1.44591,  0.750279,
  //     1.09654,  1.06207,  1.47637,  1.54455, 1.63089, 1.45489,  1.30553,
  //     1.40512,  1.39714,  1.79236,  1.49736};

  // best so far
  // const vector<double> ws{
  //     0.5711211, 0.9049245, 0.8981427, 0.9328301, 1.4871242,  1.3311178,
  //     0.1569599, 1.2237180, 1.5108654, 1.6015225, 2.4655746,  0.9778833,
  //     1.4891024, 1.0098682, 1.0574293, 0.8816649, -0.0784573, 1.5609918,
  //     1.1897258, 1.6156149, 1.3998372, 1.6612096, 1.4784579,  2.2644066,
  //     1.8542568, 1.1360595, 2.2405842, 2.3447212, 2.5901114,  1.0496764,
  //     1.1907954, 2.234827};
  const vector<double> ws{
      0.7016446,  0.0319992,  1.0452498,  -0.1884647, 0.1944772,  0.8755333,
      -0.1164212, -0.2827134, -0.2493942, 0.4862238,  0.0601287,  0.4294675,
      0.2514273,  0.9162648,  0.8660054,  0.4762087,  0.1244866,  0.4234133,
      -0.0075665, 0.9745939,  1.0002273,  0.0898837,  -0.2035567, 0.4605047,
      0.1856643,  -0.3384170, 0.0112903,  0.2442973,  -0.2190458, 0.2496235,
      1.4671965,  0.730953};

  double dval = 0.;
  for (int i = 0; i < 32; ++i) {
    dval += (GET_64(bk, i) + 2 * GET_64(bk, i + 32)) * ws[i];
    dval += (GET_64(wt, i) + 2 * GET_64(wt, i + 32)) * -ws[i];
  }

  // round and bound
  int val = round(1e5 * dval);
  val = min(BLACK_WIN_VALUE, max(WHITE_WIN_VALUE, val));

  return val;
}

static double objective(const double* ws, const int& n) {
  assert(n == N_DIM);

  const ValueEstimator vfunc = bind(value_func_cmaes, placeholders::_1,
                                    placeholders::_2, placeholders::_3, ws);

  const Strategy bk_strategy = bound_negamax_ab_strategy(2, vfunc);
  const Strategy wt_strategy = bound_negamax_ab_strategy(2, value_func_1);

  GameStats stats = run_contest(bk_strategy, wt_strategy, 100);
  double score = (stats.wt_wins + 0.5 * stats.draws) / (double)stats.n_games;
  // printf("wt %3lu   score %10.8f   xs %s\n", stats.wt_wins, score,
  //        "-");  // stringify(ws).c_str());

  //   const double z = fabs(ws[0]) + fabs(ws[1]) + fabs(ws[2]) + fabs(ws[3]);
  //   score += pow(z - 1., 2.);

  // since we're playing black's strategy, we minimize the number of white wins
  return score;
};

// custom progress function
template <class TCovarianceUpdate, class TGenoPheno>
int progress_update(const CMAParameters<TGenoPheno>& cmaparams,
                    const CMASolutions& cmasols) {
  static double elapsed = 0.0;
  elapsed += cmasols.elapsed_last_iter() / 1000.;
  printf("it=%4d  f-val=%.6f  sigma=%.6f  elapsed=%8.3f\n", cmasols.fevals(),
         cmasols.best_candidate().get_fvalue(), cmasols.sigma(), elapsed);

  ofstream ofs("cmaes_best.txt");
  ofs << stringify(cmasols.best_candidate().get_x_ptr()) << endl;
  ofs.close();

  return cmasols.niter() > 100;
}

void run_cmaes() {
  ProgressFunc<CMAParameters<GenoPheno<pwqBoundStrategy>>, CMASolutions> prog =
      &progress_update<CovarianceUpdate, GenoPheno<pwqBoundStrategy>>;

  vector<double> x0;
  double lbounds[N_DIM];
  double ubounds[N_DIM];
  for (int i = 0; i < N_DIM; ++i) {
    x0.push_back(0.3 + 0.4 * uniform(eng));
    lbounds[i] = 0.;
    ubounds[i] = 1.;
  }
  const double sigma0 = 0.3;
  const int lambda = -1;  // offspring at each generation
  assert(x0.size() == N_DIM);

  // docs:
  // https://github.com/CMA-ES/libcmaes/blob/master/include/libcmaes/cmaparameters.h
  GenoPheno<pwqBoundStrategy> gp(lbounds, ubounds, N_DIM);
  CMAParameters<GenoPheno<pwqBoundStrategy>> param(x0, sigma0, lambda, 0, gp);
  param.set_algo(
      aCMAES);  // CMAES_DEFAULT, IPOP_CMAES, aCMAES, sepacmaes (large problems)
  param.set_lazy_update(true);
  param.set_elitism(1);
  param.set_mt_feval(false);  // parallel func eval

  FitFunc ff = objective;  // cmaes library requires l-value in cmaes() ctor

  CMASolutions solutions = cmaes<>(ff, param, prog);
  const Candidate& best = solutions.best_candidate();
  cout << "best solution: " << stringify(best.get_x_ptr()) << endl;
  cout << "elapsed " << solutions.elapsed_time() / 1000.0 << " sec\n";
}

}  // namespace shashki
