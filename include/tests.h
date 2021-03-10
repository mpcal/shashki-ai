#pragma once

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>
#include "board.h"

namespace shashki {

// runs all tests
void test_all();

// utility comparing the two move vectors as sets
bool same_move_options(const std::vector<Move>& xs, const std::vector<Move>& ys,
                       bool verbose = false);

// alternate implementation of valid_moves for validating the code-generated
// version. expected to return the exact same moves given the equal inputs
std::vector<Move> valid_moves_alternate_impl(const Slice& bk, const Slice& wt,
                                             bool blacks_turn);

// see valid_moves_alternate_impl()
std::vector<Move> valid_capturing_moves_from_alternate_impl(const Slice& bk,
                                                            const Slice& wt,
                                                            bool blacks_turn,
                                                            const Loc& ix);

// see valid_moves_alternate_impl()
bool do_move_alternate_impl(Slice& s1, Slice& s2, const Move& move, const bool blacks_turn);

}  // namespace shashki
