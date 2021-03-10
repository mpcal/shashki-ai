#pragma once

#include "board.h"

namespace shashki {

int value_func_cmaes(const Slice &bk, const Slice &wt, bool, const double *w);

void run_cmaes();

void run_coevolution();

void generate_mc_data();

}  // namespace shashki
