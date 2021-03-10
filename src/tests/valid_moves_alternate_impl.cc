#include <cassert>
#include <unordered_set>
#include "_board_internal.h"
#include "tests.h"

using namespace std;

namespace shashki {

template <const int_fast8_t *fwd_offsets>
static void _add_men_moves_backward(const Loc &ix,
                                    const BoundsPredicate &one_more,
                                    const Slice &is_empty,
                                    const Slice &bottom_any,
                                    vector<Move> &mandatory) {
  if (!one_more(ix)) return;

  // selector for offsets: 0 for even rows and 1 for odd rows
  uint_fast8_t off_sel = (ix / 4) % 2;

  int_fast8_t ix_1 = ix + fwd_offsets[off_sel];

  // opponent in next square, still on board, square behind opponent empty?
  if (GET_64(bottom_any, ix_1) && one_more(ix_1) &&
      GET_64(is_empty, ix_1 + fwd_offsets[1 - off_sel]))
    mandatory.push_back(make_move(ix, ix_1 + fwd_offsets[1 - off_sel]));
}

template <const int_fast8_t *fwd_offsets>
static void _add_men_moves_forward(
    const Loc &ix, const BoundsPredicate &one_more, const Slice &is_empty,
    const Slice &bottom_any, vector<Move> &regular, vector<Move> &mandatory) {
  if (!one_more(ix)) return;

  // selector for offsets: 0 for even rows and 1 for odd rows
  uint_fast8_t off_sel = (ix / 4) % 2;

  int_fast8_t ix_1 = ix + fwd_offsets[off_sel];

  // next square empty?
  if (GET_64(is_empty, ix_1) && mandatory.empty())
    regular.push_back(make_move(ix, ix_1));

  // opponent in next square, still on board, square behind opponent empty?
  else if (GET_64(bottom_any, ix_1) && one_more(ix_1) &&
           GET_64(is_empty, ix_1 + fwd_offsets[1 - off_sel]))
    mandatory.push_back(make_move(ix, ix_1 + fwd_offsets[1 - off_sel]));
}

// ix: start index
template <const int_fast8_t *fwd_offsets>
static void _add_king_moves(const Loc &ix, const BoundsPredicate &one_more,
                            const Slice &is_empty, const Slice &bottom_any,
                            vector<Move> &regular, vector<Move> &mandatory,
                            vector<Move> &priority) {
  // selector for offsets: 0 for even rows and 1 for odd rows
  uint_fast8_t off_sel = (ix / 4) % 2;

  bool captured = false;  // remember if we already captured on this beam
  Loc from = ix;          // "local" start index a.o.t. global one `ix`
  for (uint_fast8_t step = 0; step < 7; ++step) {  // max 7 steps possible
    if (!one_more(from)) break;

    const Loc &to = from + fwd_offsets[off_sel];

    // next square empty?
    if (GET_64(is_empty, to)) {
      if (captured) {
        const Move &move = make_move(ix, to);

        // any subsequent capture? that'll be a priority move
        const bool &subseq_capture = _can_king_capture_from<fwd_offsets>(
            to, one_more, is_empty, bottom_any);

        if (subseq_capture)
          priority.push_back(move);
        else
          mandatory.push_back(move);
      } else
        regular.push_back(make_move(ix, to));

    }
    // have adjacant opponent
    // - which is not sitting on edge with free spot
    // - with and empty spot behind
    // - and we haven't yet captured on this beam
    else if (GET_64(bottom_any, to) && one_more(to) &&
             GET_64(is_empty, to + fwd_offsets[1 - off_sel]) && !captured) {
      const Loc &after_to = to + fwd_offsets[1 - off_sel];
      const Move &move = make_move(ix, after_to);
      if (_can_king_capture_from<fwd_offsets>(after_to, one_more, is_empty,
                                              bottom_any)) {
        // printf("add priority (jumping): %s\n", to_string(move).c_str());
        priority.push_back(move);
      } else {
        // printf("add mandatory (jumping): %s\n", to_string(move).c_str());
        mandatory.push_back(move);
      }

      // continue until next non-empty spot, then terminate
      from = to;              // one step forward (2nd forward at end of loop)
      off_sel = 1 - off_sel;  // flip because of the step we just did
      captured = true;
    }
    // rest of this beam is blocked
    else {
      break;
    }

    from += fwd_offsets[off_sel];
    off_sel = 1 - off_sel;
  }
}

// add all possible men moves in all directions, playing top-down
static inline void _add_men_moves_for_ix(const Loc &ix, const Slice &is_empty,
                                         const Slice &bottom_any,
                                         vector<Move> &regular,
                                         vector<Move> &mandatory) {
  _add_men_moves_backward<ne_offsets>(ix, one_more_ne, is_empty, bottom_any,
                                      mandatory);
  _add_men_moves_backward<nw_offsets>(ix, one_more_nw, is_empty, bottom_any,
                                      mandatory);
  _add_men_moves_forward<sw_offsets>(ix, one_more_sw, is_empty, bottom_any,
                                     regular, mandatory);
  _add_men_moves_forward<se_offsets>(ix, one_more_se, is_empty, bottom_any,
                                     regular, mandatory);
}

// add all possible king moves in all directions, playing top-down
static void _add_king_moves_for_ix(const Loc &ix, const Slice &is_empty,
                                   const Slice &bottom_any,
                                   vector<Move> &regular,
                                   vector<Move> &mandatory,
                                   vector<Move> &priority) {
  _add_king_moves<ne_offsets>(ix, one_more_ne, is_empty, bottom_any, regular,
                              mandatory, priority);
  _add_king_moves<nw_offsets>(ix, one_more_nw, is_empty, bottom_any, regular,
                              mandatory, priority);
  _add_king_moves<sw_offsets>(ix, one_more_sw, is_empty, bottom_any, regular,
                              mandatory, priority);
  _add_king_moves<se_offsets>(ix, one_more_se, is_empty, bottom_any, regular,
                              mandatory, priority);
}

// assuming it's the top player's turn (playing top to bottom), add all valid
// moves to moves
static vector<Move> _valid_moves_top_down(const Slice &top,
                                          const Slice &bottom) {
  vector<Move> regular, mandatory, priority;

  // "any" slices: bit i set if the player has any token at location i, only
  // lower 32 bits are valid
  const Slice top_any = ((top >> 32) | top) & 0xffffffff;
  const Slice bottom_any = ((bottom >> 32) | bottom) & 0xffffffff;

  // slice with bit i set if the board location has no token
  const Slice is_empty = ~(top_any | bottom_any) & 0xffffffff;

  // find valid moves for all men
  for (Loc ix = 0; ix < 32; ++ix) {
    if (!GET_64(top, ix)) continue;
    _add_men_moves_for_ix(ix, is_empty, bottom_any, regular, mandatory);
  }

  // find valid moves for all kings
  Slice top_kings = top >> 32;
  for (Loc ix = 0; ix < 32; ++ix) {
    if (!GET_64(top_kings, ix)) continue;
    _add_king_moves_for_ix(ix, is_empty, bottom_any, regular, mandatory,
                           priority);
  }

  // remove mandatory which share the origin with any priority moves but keep
  // the other mandatory moves
  std::unordered_set<Loc> hot_fields;
  std::transform(priority.begin(), priority.end(),
                 std::inserter(hot_fields, hot_fields.end()), get_from);
  std::copy_if(mandatory.begin(), mandatory.end(), std::back_inserter(priority),
               [&hot_fields](const Move &m) {
                 return hot_fields.find(get_from(m)) == hot_fields.end();
               });

  return !priority.empty() ? priority : regular;
}

// Same as _valid_moves_top_down(), except:
// * only moves for a single token at `ix` are considered;
// * all of these moves must capture an enemy token or they won't be returned
static vector<Move> _mandatory_moves_top_down_for_ix(const Loc &ix,
                                                     const Slice &top,
                                                     const Slice &bottom) {
  vector<Move> regular, mandatory, priority;

  // "any" slices: bit i set if the player has any token at location i, only
  // lower 32 bits are valid
  const Slice top_any = ((top >> 32) | top) & 0xffffffff;
  const Slice bottom_any = ((bottom >> 32) | bottom) & 0xffffffff;

  // slice with bit i set if the board location has no token
  const Slice is_empty = ~(top_any | bottom_any) & 0xffffffff;

  // find valid moves for all the men
  if (GET_64(top, ix))
    _add_men_moves_for_ix(ix, is_empty, bottom_any, regular, mandatory);

  // find valid moves for all the kings
  if (GET_64(top >> 32, ix))
    _add_king_moves_for_ix(ix, is_empty, bottom_any, regular, mandatory,
                           priority);

  return !priority.empty() ? priority : mandatory;
}

vector<Move> valid_moves_alternate_impl(const Slice &bk, const Slice &wt,
                                        bool blacks_turn) {
  vector<Move> moves;

  if (blacks_turn) {
    moves = _valid_moves_top_down(bk, wt);
  } else {
    // flip board upside down
    const Slice &bk_flip = rotate_slice(bk);
    const Slice &wt_flip = rotate_slice(wt);

    // play usual top-down
    moves = _valid_moves_top_down(wt_flip, bk_flip);

    // translate moves back: m --> 31 - m, i.e. take their one-complement (or
    // simply binary "not"); uses above condition that the two times three
    // superfluous bits of each move may have arbitrary values
    for (Move &m : moves) m = ~m;
  }

  // xxx debug
  // if (ix < 32) {
  //   vector<Move> buf;
  //   copy_if(moves.begin(), moves.end(), back_inserter(buf),
  //           [&ix](const Move &mv) { return get_from(mv) == ix; });
  //   moves = buf;
  // }

  return moves;
}

vector<Move> valid_capturing_moves_from_alternate_impl(const Slice &bk,
                                                       const Slice &wt,
                                                       bool blacks_turn,
                                                       const Loc &ix) {
  assert(0 <= ix && ix < 32 &&
         ((blacks_turn && (GET_64(bk, ix) || GET_64(bk, ix + 32))) ||
          (!blacks_turn && (GET_64(wt, ix) || GET_64(wt, ix + 32)))));

  vector<Move> moves;

  if (blacks_turn) {
    moves = _mandatory_moves_top_down_for_ix(ix, bk, wt);
  } else {
    // flip board upside down
    const Slice &bk_flip = rotate_slice(bk);
    const Slice &wt_flip = rotate_slice(wt);
    const Loc &ix_flip = 31 - ix;

    // play usual top-down
    moves = _mandatory_moves_top_down_for_ix(ix_flip, wt_flip, bk_flip);

    // translate moves back: m --> 31 - m, i.e. take their one-complement (or
    // simply binary "not"); uses above condition that the two times three
    // superfluous bits of each move may have arbitrary values
    for (Move &m : moves) m = ~m;
  }

  return moves;
}

}  // namespace shashki
