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

static double fitness_prototype(const double* bk_w, const double* wt_w,
                                const int& n, const bool bk_opt) {
  assert(n == N_DIM);

  const ValueEstimator val_bk = bind(value_func_cmaes, placeholders::_1,
                                     placeholders::_2, placeholders::_3, bk_w);
  const ValueEstimator val_wt = bind(value_func_cmaes, placeholders::_1,
                                     placeholders::_2, placeholders::_3, wt_w);
  const GameStats stats =
      run_contest(bound_negamax_ab_strategy(bk_opt ? 1 : 2, val_bk),
                  bound_negamax_ab_strategy(bk_opt ? 2 : 1, val_wt), 200);

  // black's minimizing the number of white wins and vice versa
  if (bk_opt)
    return (stats.wt_wins + 0.5 * stats.draws) / (double)stats.n_games;
  else
    return (stats.bk_wins + 0.5 * stats.draws) / (double)stats.n_games;
};

// custom progress function
template <class TCovarianceUpdate, class TGenoPheno>
int progress_update(const CMAParameters<TGenoPheno>& cmaparams,
                    const CMASolutions& cmasols) {
  static double elapsed = 0.0;
  elapsed += cmasols.elapsed_last_iter() / 1000.;
  printf("feval=%4d  f-val=%.6f  sigma=%.6f  elapsed=%8.3f\n", cmasols.fevals(),
         cmasols.best_candidate().get_fvalue(), cmasols.sigma(), elapsed);

  ofstream ofs("cmaes_best.txt");
  ofs << stringify(cmasols.best_candidate().get_x_ptr()) << endl;
  ofs.close();

  return 0;  // cmasols.niter() > 100;
}

void run_coevolution() {
  const string best_bk_file = "cmaes_best_bk.txt";
  const string best_wt_file = "cmaes_best_wt.txt";
  remove(best_bk_file.c_str());
  remove(best_wt_file.c_str());

  double best_bk[N_DIM];  // best solution for black
  double best_wt[N_DIM];  // best solution for white
  double lbounds[N_DIM];
  double ubounds[N_DIM];
  for (int i = 0; i < N_DIM; ++i) {
    best_bk[i] = 0.3 + 0.4 * uniform(eng);
    best_wt[i] = 0.3 + 0.4 * uniform(eng);
    lbounds[i] = 0.;
    ubounds[i] = 1.;
  }
  const double EPOCHS = 20;
  const double sigma0 = 0.2;

  ProgressFunc<CMAParameters<GenoPheno<pwqBoundStrategy>>, CMASolutions> prog =
      &progress_update<CovarianceUpdate, GenoPheno<pwqBoundStrategy>>;

  for (int epoch = 0; epoch < EPOCHS; ++epoch) {
    // is black currently optimizing (and white sparring)?
    const bool bk_opt = epoch % 2 == 0;

    printf("====================== Epoch %d (%s opt) ======================\n",
           epoch, bk_opt ? "bk" : "wt");

    // define fitness function
    FitFunc fitness;
    if (bk_opt)
      fitness = bind(fitness_prototype, placeholders::_1, best_wt,
                     placeholders::_2, true);
    else
      fitness = bind(fitness_prototype, best_bk, placeholders::_1,
                     placeholders::_2, false);

    // https://github.com/CMA-ES/libcmaes/blob/master/include/libcmaes/cmaparameters.h
    // CMAES_DEFAULT, IPOP_CMAES, aCMAES, sepacmaes (large problems)
    const int lambda = -1;  // offspring at each generation
    const double sigma = (1. - (double)epoch / EPOCHS) * sigma0;  // annealing
    const vector<double> x0(bk_opt ? best_bk : best_wt,
                            bk_opt ? best_bk + N_DIM : best_wt + N_DIM);

    GenoPheno<pwqBoundStrategy> gp(lbounds, ubounds, N_DIM);
    CMAParameters<GenoPheno<pwqBoundStrategy>> param(x0, sigma, lambda, 0, gp);
    param.set_max_fevals(300);
    param.set_algo(aCMAES);
    // param.set_lazy_update(true);
    param.set_elitism(1);
    // param.set_mt_feval(true);  // parallel func eval

    // run solver
    const CMASolutions pop =
        cmaes<GenoPheno<pwqBoundStrategy>>(fitness, param, prog);

    // update optimized strategy
    const Candidate& best = pop.best_candidate();
    copy(best.get_x_ptr(), best.get_x_ptr() + N_DIM,
         bk_opt ? best_bk : best_wt);

    // dump current best solutions to disk
    ofstream(best_bk_file, ios_base::app)
        << epoch << ", " << setprecision(4) << best.get_fvalue() << ", "
        << pop.sigma() << ", " << stringify(best_bk) << endl;
    ofstream(best_wt_file, ios_base::app)
        << epoch << ", " << setprecision(4) << best.get_fvalue() << ", "
        << pop.sigma() << ", " << stringify(best_wt) << endl;

    printf("Best solution for %s: f-val = %.4f +/- %.6f, elapsed %.3f s\n",
           bk_opt ? "black" : "white", best.get_fvalue(), pop.sigma(),
           pop.elapsed_time() / 1000.);
  }
}

}  // namespace shashki
