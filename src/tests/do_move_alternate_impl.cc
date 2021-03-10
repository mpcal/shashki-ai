#include <cassert>
#include "_board_internal.h"
// #include "tests.h"

using namespace std;

namespace shashki {

bool do_move_alternate_impl(Slice &s1, Slice &s2, const Move &move, const bool blacks_turn) {
  // get move indixes
  Loc from = get_from(move);
  const Loc &to = get_to(move);

  // the rest of the code requires s1 be the active player
  bool swapped = false;
  if (GET_64(s2, from) || GET_64(s2, from + 32)) {
    std::swap(s1, s2);
    swapped = true;
  }

  // pick right offset sequence for the direction of movement
  const int_fast8_t *fwd_offsets;
  if (from > to)
    fwd_offsets = col_of[from] < col_of[to] ? ne_offsets : nw_offsets;
  else
    fwd_offsets = col_of[from] > col_of[to] ? sw_offsets : se_offsets;

  // selector for offsets: 0 for even `from` rows, 1 for odd rows
  uint_fast8_t off_sel = (from / 4) % 2;

  const bool is_king = GET_64(s1 >> 32, from);
  assert(GET_64(s1 >> (32 * is_king), from));

  // actual move, assert destination is empty
  CLEAR_64(s1, from + 32 * is_king);
  assert(!GET_64(s1, to) && !GET_64(s1, to + 32) && !GET_64(s2, to) &&
         !GET_64(s1, to + 32));
  SET_64(s1, to + 32 * is_king);

  // walk from `from` to `to`, capturing at most one token in between
  bool captured = false;
  for (uint_fast8_t step = 0; step < 7; ++step) {  // max 7 steps possible
    from += fwd_offsets[off_sel];
    if (from == to) break;

    // assert no double-capture
    assert(!(captured && (GET_64(s2, from) || GET_64(s2, from + 32))));
    captured |= GET_64(s2, from) || GET_64(s2, from + 32);

    CLEAR_64(s2, from);
    CLEAR_64(s2, from + 32);

    off_sel = 1 - off_sel;
  }
  assert(from == to);

  // swap them back
  if (swapped) std::swap(s1, s2);

  // a man reaching the opponent's kings row becomes a king himself
  if ((to / 4 == 7 && blacks_turn || to / 4 == 0 &&  !blacks_turn) && GET_64(s1, to)) {
    CLEAR_64(s1, to);
    SET_64(s1, to + 32);
  }

  return captured;
}

}  // namespace shashki
