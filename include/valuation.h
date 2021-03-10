#pragma once

#include <functional>
#include "board.h"

namespace shashki {

// Values all ValueEstimator function shall return in case black or white,
// respectively, wins. The defined values below are large in absolute value,
// but still leave a some leeway to integer limits to avoid hard to detect
// overflows
//
// Also used to initialize alpha and beta in negamax pruning which requires
// WHITE_WIN_VALUE be smaller than (or equal to) any possible value an estimator
// will return. Likewise BLACK_WIN_VALUE must be larger than (or equal to) the
// largest possible value
constexpr int BLACK_WIN_VALUE = 2000000000;
constexpr int WHITE_WIN_VALUE = -2000000000;

/**
 * Type which all value funcction shall implement
 *
 * Returns an estimate of how promising the given board from *for black*
 * perspective, higher values are better. Note that this makes black the
 * maximizing player
 */
using ValueEstimator = std::function<int(const Slice &, const Slice &,
                                         const bool, const uint_fast8_t)>;
int vfunc_basic(const Slice &bk, const Slice &wt, const bool blacks_turn,
                const uint_fast8_t cur_depth);
int vfunc_rollout(const Slice &bk, const Slice &wt, const bool blacks_turn,
                  const uint_fast8_t cur_depth);
int vfunc_basic_rollout(const Slice &bk, const Slice &wt,
                        const bool blacks_turn, const uint_fast8_t cur_depth);

// additional value function provided in binary form only, defined in
// lib/external_vfunc.cc.o; comment out in case linking fails
int vfunc_external_1(const Slice &bk, const Slice &wt, bool blacks_turn,
                     const uint_fast8_t cur_depth);

}  // namespace shashki
