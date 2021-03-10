#pragma once

#include <cassert>
#include <string>
#include <vector>

namespace shashki {

/**
 * Bit manipulation ops
 */

inline uint_fast64_t GET_64(const uint_fast64_t &x, const uint_fast8_t &i) {
  return (x >> i) & 1UL;
}

inline void SET_64(uint_fast64_t &x, const uint_fast8_t &i) { x |= 1UL << i; }

inline void CLEAR_64(uint_fast64_t &x, const uint_fast8_t &i) {
  x &= ~(1UL << i);
}

/**
 * Board layout. Each player requires 64 bits, referred to as a slice. The lower
 * 32 bits indicate the position of the men, the upper 32 bits those of the
 * kings:
 *
 *                       |  0   1   2   3   4   5   6   7 |
 *                     --|--------------------------------|
 *                     0 |  ·   0   ·   1   ·   2   ·   3 |
 *                     1 |  4   ·   5   ·   6   ·   7     |
 *                     2 |  ·   8   ·   9   ·  10   ·  11 |
 *         bk, wt  :=  3 | 12   ·  13   ·  14   ·  15     |
 *                     4 |  ·  16   ·  17   ·  18   ·  19 |
 *                     5 | 20   ·  21   ·  22   ·  23     |
 *                     6 |  ·  24   ·  25   ·  26   ·  27 |
 *                     7 | 28   ·  29   ·  30   ·  31   · |
 *                     --|--------------------------------|
 *
 * DO NOT MODIFY--this is a convenience alias and the implementation may
 * implicitly assume unsigned-ness and/or a width of 64 bits.
 */
using Slice = uint_fast64_t;

/**
 * Move layout. stored as ushort, low byte designates the "from" location, the
 * high byte the "to" location. Note that both of them will be in {0, 1, ...,
 * 32} and thus only use the first 5 bits of the respective byte:
 *
 *                  move := ? ? ? t t t t t ? ? ? f f f f f
 *
 * where the remaining 6 bits' values are undefined. In any case it's true that
 * from == move & 31, to == move & (31 << 8)
 *
 * DO NOT MODIFY--this is a convenience alias and the implementation may
 * implicitly assume unsigned-ness and/or a width of 16 bits or more
 */
using Move = uint_fast16_t;
constexpr uint_fast16_t NO_MOVE = 0;  // special value: not a valid move

/**
 * Location on the board. While a uint_fast8_t would suffice, we still use an
 * uint_fast16_t because of the definition of the Move above. This will pay off
 * in the construction of a move (which is a frequent operation) where we can
 * just shift two Loc into a Move without conversion
 *
 * DO NOT MODIFY--this is a convenience alias and the implementation may
 * implicitly assume unsigned-ness and/or a minimum width of 16 bits
 */
using Loc = uint_fast16_t;
constexpr uint_fast16_t NO_LOC = 0xffff;  // special value: not a valid location

// create move given origin and destination locations
inline Move make_move(const Loc &from, const Loc &to) {
  return (to << 8) + from;
}

// returns a clean version of the move with all unused bits set to 0
inline Move clean_move(Move mv) { return mv & 0b0001111100011111; }

// returns origin for move
inline Loc get_from(Move mv) { return mv & 31; }

// returns destination for move
inline Loc get_to(Move mv) { return (mv >> 8) & 31; }

// returns the men positions part of the Slice as a 32-bit uint
inline uint_fast32_t get_men_32(const Slice &slc) {
  return static_cast<uint_fast32_t>(slc & 0xffffffffUL);
}

// returns the kings positions part of the Slice as a 32-bit uint
inline uint_fast32_t get_kings_32(const Slice &slc) {
  return static_cast<uint_fast32_t>(slc >> 32);
}

// string representation for move
std::string to_string(const Move &mv);

/**
 * Rotates a slice by 180 degrees. This is equivalent to reversing the order of
 * bits in the slice, seperately for the lower and the upper 32-bit block, cf.
 * https://cutt.ly/LjxpWMK
 */
Slice rotate_slice(const Slice &slice);

/**
 * Flips the board upside down
 */
Slice flip_slice(const Slice &slice);

// returns all valid moves for the given slice
std::vector<Move> valid_moves(const Slice &bk, const Slice &wt,
                              bool blacks_turn);

// returns the CAPTURING moves starting from ix
std::vector<Move> valid_capturing_moves_from(const Slice &bk, const Slice &wt,
                                             const Loc &ix);

// prints board to stdout; `options` and `highlight` are optional
void print_board(const Slice &bk, const Slice &wt,
                 const std::vector<Move> &options = std::vector<Move>(),
                 const Move *const highlight = nullptr);

// returns true if board is valid: max 12 tokens per player and no two tokens in
// the same spot (men and kings of black and white)
bool board_valid(const Slice &bk, const Slice &wt);

// intializes a board randomly
void random_board(Slice &bk, Slice &wt, double p_skip_token = 0.5,
                  double p_is_king = 0.05);

/**
 * Executes a move for black. Assumes the given move is valid. Returns whether
 * or not a capture occurred
 *
 * Note: Whether it's black's or white's turn is already implicit in `move`. For
 * efficiency however we avoid recomputing this as it's typically already known
 * at the call site
 */
bool do_move_bk(Slice &bk, Slice &wt, const Move &move);

/** Executes a move for white. See also do_move_bk() */
bool do_move_wt(Slice &bk, Slice &wt, const Move &move);

/**
 * Executes the given move and returns whether or not a capture occurred
 */
inline bool do_move(Slice &bk, Slice &wt, const Move &move) {
  const Loc &from = get_from(move);
  const Loc &to = get_to(move);
  const bool blacks_turn = GET_64(bk, from) || GET_64(bk, from + 32);
  assert(blacks_turn &&
             (GET_64(wt, from) == 0UL && GET_64(wt, from + 32) == 0UL) ||
         !blacks_turn &&
             (GET_64(bk, from) == 0UL && GET_64(bk, from + 32) == 0UL));
  assert(GET_64(bk, to) == 0UL && GET_64(bk, to + 32) == 0UL &&
         GET_64(wt, to) == 0UL && GET_64(wt, to + 32) == 0UL);

  return blacks_turn ? do_move_bk(bk, wt, move) : do_move_wt(bk, wt, move);
}

}  // namespace shashki
