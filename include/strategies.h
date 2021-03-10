/** Strategy declarations. Most of them have an extra function prefixed by
 * `bound_` which binds extra parameters (w.r.t. `Strategy`) to a function
 * object and returns the something that is a `Strategy`
 */

#pragma once

#include <limits.h>
#include <cassert>
#include <cstdint>
#include <functional>
#include <memory>
#include <random>
#include <stdexcept>
#include "board.h"
#include "nlohmann/json.hpp"
#include "valuation.h"

namespace shashki {

/**
 * Selects a move under the implemented strategy
 *
 * Return value: the selected move or NO_MOVE, if there's no feasible move
 *
 * Args
 * - bk: the black 64-bit slice of the board
 * - wt: the white 64-bit slice of the board
 * - blacks_true: true if black is to make the next move, false otherwise
 * - from: location to start the move from, used for capturing moves; `from` in
 * 0..31 implies that the move must be capturing; `from == NO_LOC` allows for
 * any valid move
 */
using Strategy = std::function<Move(const Slice& bk, const Slice& wt,
                                    const bool blacks_turn, const Loc& from)>;

// Random strategy
Move random_strategy(const Slice&, const Slice&, const bool blacks_turn,
                     const Loc& from);

// Minimax/negamax with alpha-beta pruning
Move negamax_ab_strategy(const Slice& bk, const Slice& wt,
                         const bool blacks_turn, const Loc& from,
                         const uint_fast8_t search_depth,
                         const ValueEstimator& value_estim,
                         nlohmann::json* explanation);

inline Strategy bound_negamax_ab_strategy(
    const uint_fast8_t search_depth, const ValueEstimator& value_estim,
    nlohmann::json* explanation = nullptr) {
  return std::bind(negamax_ab_strategy, std::placeholders::_1,
                   std::placeholders::_2, std::placeholders::_3,
                   std::placeholders::_4, search_depth, value_estim,
                   explanation);
}

}  // namespace shashki
