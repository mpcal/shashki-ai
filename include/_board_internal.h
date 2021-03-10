#pragma once

#include <functional>
#include "board.h"

namespace shashki {

// offsets: looking from an even row (zero-based), the north-east neighbor will
// be at offset -3, while the same offset will be -4 when starting from an odd
// row
static constexpr int_fast8_t ne_offsets[2] = {-3, -4};
static constexpr int_fast8_t nw_offsets[2] = {-4, -5};
static constexpr int_fast8_t sw_offsets[2] = {4, 3};
static constexpr int_fast8_t se_offsets[2] = {5, 4};

// lookup-table for 0-based column index given the board index
static constexpr int col_of[32] = {1, 3, 5, 7, 0, 2, 4, 6, 1, 3, 5,
                                   7, 0, 2, 4, 6, 1, 3, 5, 7, 0, 2,
                                   4, 6, 1, 3, 5, 7, 0, 2, 4, 6};

// static constexpr array<array<int, 5>, 32> neighbors = {
//   {}
// };

// predicate returning true if there's at least one other field on the board in
// direction NE/NW/SW/SE when starting from the given location
using BoundsPredicate = std::function<bool(const Loc &)>;
inline static const BoundsPredicate one_more_ne = [](const Loc &ix) {
  return ix > 3 && (ix - 3) % 8 != 0;
};
inline static const BoundsPredicate one_more_nw = [](const Loc &ix) {
  return ix > 4 && (ix - 4) % 8 != 0;
};
inline static const BoundsPredicate one_more_sw = [](const Loc &ix) {
  return ix < 28 && (ix - 4) % 8 != 0;
};
inline static const BoundsPredicate one_more_se = [](const Loc &ix) {
  return ix < 27 && (ix - 3) % 8 != 0;
};

// expose internally some functions for testing

// Returns true if at least one capture along the beam defined by `ix` and
// `offsets` is possible and false otherwise
inline bool _can_king_capture_along_beam(const Loc &ix,
                                         const int_fast8_t *fwd_offsets,
                                         const BoundsPredicate &one_more,
                                         const Slice &is_empty,
                                         const Slice &bottom_any) {
  // selector for offsets: 0 for even rows and 1 for odd rows
  uint_fast8_t off_sel = (ix / 4) % 2;

  const Slice bk = ~(is_empty | bottom_any);

  Loc from = ix;  // "local" start index a.o.t. global one `ix`
  for (uint_fast8_t step = 0; step < 7; ++step) {  // max 7 steps possible
    if (!one_more(from) || GET_64(bk, from)) return false;

    const Loc &to = from + fwd_offsets[off_sel];
    if (GET_64(bottom_any, to) && one_more(to))
      return GET_64(is_empty, to + fwd_offsets[1 - off_sel]);

    from += fwd_offsets[off_sel];
    off_sel = 1 - off_sel;
  }

  return false;
}

inline void _get_ortho_offsets_and_predicates(const int_fast8_t *fwd_offsets,
                                              const int_fast8_t *&off_1,
                                              const int_fast8_t *&off_2,
                                              const BoundsPredicate *&pred_1,
                                              const BoundsPredicate *&pred_2) {
  if (fwd_offsets[0] == ne_offsets[0] && fwd_offsets[1] == ne_offsets[1] ||
      fwd_offsets[0] == sw_offsets[0] && fwd_offsets[1] == sw_offsets[1]) {
    off_1 = nw_offsets;
    pred_1 = &one_more_nw;
    off_2 = se_offsets;
    pred_2 = &one_more_se;
  } else if (fwd_offsets[0] == nw_offsets[0] &&
                 fwd_offsets[1] == nw_offsets[1] ||
             fwd_offsets[0] == se_offsets[0] &&
                 fwd_offsets[1] == se_offsets[1]) {
    off_1 = ne_offsets;
    pred_1 = &one_more_ne;
    off_2 = sw_offsets;
    pred_2 = &one_more_sw;
  } else
    throw std::runtime_error("Invalid offset :/");
}

template <const int_fast8_t *fwd_offsets>
inline bool _can_king_capture_from(const Loc &ix,
                                   const BoundsPredicate &one_more_fwd,
                                   const Slice &is_empty,
                                   const Slice &bottom_any) {
  // any subsequent capture? that'll be a priority move
  const int_fast8_t *off_1, *off_2;
  const BoundsPredicate *pred_1, *pred_2;
  _get_ortho_offsets_and_predicates(fwd_offsets, off_1, off_2, pred_1, pred_2);

  return
      // forward?
      _can_king_capture_along_beam(ix, fwd_offsets, one_more_fwd, is_empty,
                                   bottom_any) ||
      // orthogonally to one side?
      _can_king_capture_along_beam(ix, off_1, *pred_1, is_empty, bottom_any) ||
      // orthogonally to the other side?
      _can_king_capture_along_beam(ix, off_2, *pred_2, is_empty, bottom_any);
}
}  // namespace shashki
