//
// Purpose: Implements do_move_bk() and do_move_wt() as declared in board.h
//
// ------------------------- WARNING - DO NOT MODIFY! --------------------------
//   This file has been generated automatically.  Modifications will be lost!
//   Generating script: generate_do_move.py
// -----------------------------------------------------------------------------
//
#include "board.h"
#include <cassert>
#include <functional>
#include <vector>

namespace shashki {

// map entry 1024 (= 0 -> 4); note that
// `s1` must be the active player
static inline bool _do_move_0_4(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 4 + 32 * GET_64(s1, 32));

  // clear `from` bit
  s1 &= 18446744069414584318UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 1280 (= 0 -> 5); note that
// `s1` must be the active player
static inline bool _do_move_0_5(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 5 + 32 * GET_64(s1, 32));

  // clear `from` bit
  s1 &= 18446744069414584318UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2304 (= 0 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_0_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 32));

  // clear `from` bit
  s1 &= 18446744069414584318UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 137438953504UL) == 0);
  const bool capture = s2 & 137438953504UL;
  s2 &= 18446743936270598111UL;

  return capture;
}

// map entry 3584 (= 0 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_0_14(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 32));

  // clear `from` bit
  s1 &= 18446744069414584318UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 2336462209568UL) == 0);
  const bool capture = s2 & 2336462209568UL;
  s2 &= 18446741737247342047UL;

  return capture;
}

// map entry 4608 (= 0 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_0_18(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 32));

  // clear `from` bit
  s1 &= 18446744069414584318UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 72705206403616UL) == 0);
  const bool capture = s2 & 72705206403616UL;
  s2 &= 18446671368503147999UL;

  return capture;
}

// map entry 5888 (= 0 -> 23); note that
// `s1` must be the active player
static inline bool _do_move_0_23(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 23 + 32 * GET_64(s1, 32));

  // clear `from` bit
  s1 &= 18446744069414584318UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1198605113508384UL) == 0);
  const bool capture = s2 & 1198605113508384UL;
  s2 &= 18445545468596043231UL;

  return capture;
}

// map entry 6912 (= 0 -> 27); note that
// `s1` must be the active player
static inline bool _do_move_0_27(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 27 + 32 * GET_64(s1, 32));

  // clear `from` bit
  s1 &= 18446744069414584318UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37227402140860960UL) == 0);
  const bool capture = s2 & 37227402140860960UL;
  s2 &= 18409516671568690655UL;

  return capture;
}

// map entry 1281 (= 1 -> 5); note that
// `s1` must be the active player
static inline bool _do_move_1_5(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 5 + 32 * GET_64(s1, 33));

  // clear `from` bit
  s1 &= 18446744065119617021UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2049 (= 1 -> 8); note that
// `s1` must be the active player
static inline bool _do_move_1_8(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 8 + 32 * GET_64(s1, 33));

  // clear `from` bit
  s1 &= 18446744065119617021UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 137438953504UL) == 0);
  const bool capture = s2 & 137438953504UL;
  s2 &= 18446743936270598111UL;

  return capture;
}

// map entry 3073 (= 1 -> 12); note that
// `s1` must be the active player
static inline bool _do_move_1_12(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 12 + 32 * GET_64(s1, 33));

  // clear `from` bit
  s1 &= 18446744065119617021UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1236950581536UL) == 0);
  const bool capture = s2 & 1236950581536UL;
  s2 &= 18446742836758970079UL;

  return capture;
}

// map entry 1537 (= 1 -> 6); note that
// `s1` must be the active player
static inline bool _do_move_1_6(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 6 + 32 * GET_64(s1, 33));

  // clear `from` bit
  s1 &= 18446744065119617021UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2561 (= 1 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_1_10(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 33));

  // clear `from` bit
  s1 &= 18446744065119617021UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 274877907008UL) == 0);
  const bool capture = s2 & 274877907008UL;
  s2 &= 18446743798831644607UL;

  return capture;
}

// map entry 3841 (= 1 -> 15); note that
// `s1` must be the active player
static inline bool _do_move_1_15(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 15 + 32 * GET_64(s1, 33));

  // clear `from` bit
  s1 &= 18446744065119617021UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 4672924419136UL) == 0);
  const bool capture = s2 & 4672924419136UL;
  s2 &= 18446739400785132479UL;

  return capture;
}

// map entry 4865 (= 1 -> 19); note that
// `s1` must be the active player
static inline bool _do_move_1_19(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 19 + 32 * GET_64(s1, 33));

  // clear `from` bit
  s1 &= 18446744065119617021UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 145410412807232UL) == 0);
  const bool capture = s2 & 145410412807232UL;
  s2 &= 18446598663296744383UL;

  return capture;
}

// map entry 1538 (= 2 -> 6); note that
// `s1` must be the active player
static inline bool _do_move_2_6(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 6 + 32 * GET_64(s1, 34));

  // clear `from` bit
  s1 &= 18446744056529682427UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2306 (= 2 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_2_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 34));

  // clear `from` bit
  s1 &= 18446744056529682427UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 274877907008UL) == 0);
  const bool capture = s2 & 274877907008UL;
  s2 &= 18446743798831644607UL;

  return capture;
}

// map entry 3330 (= 2 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_2_13(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 34));

  // clear `from` bit
  s1 &= 18446744056529682427UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 2473901163072UL) == 0);
  const bool capture = s2 & 2473901163072UL;
  s2 &= 18446741599808388543UL;

  return capture;
}

// map entry 4098 (= 2 -> 16); note that
// `s1` must be the active player
static inline bool _do_move_2_16(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 16 + 32 * GET_64(s1, 34));

  // clear `from` bit
  s1 &= 18446744056529682427UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37658273260096UL) == 0);
  const bool capture = s2 & 37658273260096UL;
  s2 &= 18446706415436291519UL;

  return capture;
}

// map entry 5122 (= 2 -> 20); note that
// `s1` must be the active player
static inline bool _do_move_2_20(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 20 + 32 * GET_64(s1, 34));

  // clear `from` bit
  s1 &= 18446744056529682427UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 319133250036288UL) == 0);
  const bool capture = s2 & 319133250036288UL;
  s2 &= 18446424940459515327UL;

  return capture;
}

// map entry 1794 (= 2 -> 7); note that
// `s1` must be the active player
static inline bool _do_move_2_7(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 7 + 32 * GET_64(s1, 34));

  // clear `from` bit
  s1 &= 18446744056529682427UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2818 (= 2 -> 11); note that
// `s1` must be the active player
static inline bool _do_move_2_11(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 11 + 32 * GET_64(s1, 34));

  // clear `from` bit
  s1 &= 18446744056529682427UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 549755814016UL) == 0);
  const bool capture = s2 & 549755814016UL;
  s2 &= 18446743523953737599UL;

  return capture;
}

// map entry 1795 (= 3 -> 7); note that
// `s1` must be the active player
static inline bool _do_move_3_7(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 7 + 32 * GET_64(s1, 35));

  // clear `from` bit
  s1 &= 18446744039349813239UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2563 (= 3 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_3_10(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 35));

  // clear `from` bit
  s1 &= 18446744039349813239UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 549755814016UL) == 0);
  const bool capture = s2 & 549755814016UL;
  s2 &= 18446743523953737599UL;

  return capture;
}

// map entry 3587 (= 3 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_3_14(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 35));

  // clear `from` bit
  s1 &= 18446744039349813239UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 4947802326144UL) == 0);
  const bool capture = s2 & 4947802326144UL;
  s2 &= 18446739125907225471UL;

  return capture;
}

// map entry 4355 (= 3 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_3_17(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 35));

  // clear `from` bit
  s1 &= 18446744039349813239UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 75316546520192UL) == 0);
  const bool capture = s2 & 75316546520192UL;
  s2 &= 18446668757163031423UL;

  return capture;
}

// map entry 5379 (= 3 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_3_21(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 35));

  // clear `from` bit
  s1 &= 18446744039349813239UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 638266500072576UL) == 0);
  const bool capture = s2 & 638266500072576UL;
  s2 &= 18446105807209479039UL;

  return capture;
}

// map entry 6147 (= 3 -> 24); note that
// `s1` must be the active player
static inline bool _do_move_3_24(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 24 + 32 * GET_64(s1, 35));

  // clear `from` bit
  s1 &= 18446744039349813239UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9645465756910720UL) == 0);
  const bool capture = s2 & 9645465756910720UL;
  s2 &= 18437098607952640895UL;

  return capture;
}

// map entry 7171 (= 3 -> 28); note that
// `s1` must be the active player
static inline bool _do_move_3_28(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 28 + 32 * (blacks_turn || GET_64(s1, 35)));

  // clear `from` bit
  s1 &= 18446744039349813239UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 81703059811615872UL) == 0);
  const bool capture = s2 & 81703059811615872UL;
  s2 &= 18365041013897935743UL;

  return capture;
}

// map entry 4 (= 4 -> 0); note that
// `s1` must be the active player
static inline bool _do_move_4_0(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 0 + 32 * (!blacks_turn || GET_64(s1, 36)));

  // clear `from` bit
  s1 &= 18446744004990074863UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2052 (= 4 -> 8); note that
// `s1` must be the active player
static inline bool _do_move_4_8(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 8 + 32 * GET_64(s1, 36));

  // clear `from` bit
  s1 &= 18446744004990074863UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3332 (= 4 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_4_13(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 36));

  // clear `from` bit
  s1 &= 18446744004990074863UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1099511628032UL) == 0);
  const bool capture = s2 & 1099511628032UL;
  s2 &= 18446742974197923583UL;

  return capture;
}

// map entry 4356 (= 4 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_4_17(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 36));

  // clear `from` bit
  s1 &= 18446744004990074863UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 36283883725056UL) == 0);
  const bool capture = s2 & 36283883725056UL;
  s2 &= 18446707789825826559UL;

  return capture;
}

// map entry 5636 (= 4 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_4_22(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 36));

  // clear `from` bit
  s1 &= 18446744004990074863UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 599233837277440UL) == 0);
  const bool capture = s2 & 599233837277440UL;
  s2 &= 18446144839872274175UL;

  return capture;
}

// map entry 6660 (= 4 -> 26); note that
// `s1` must be the active player
static inline bool _do_move_4_26(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 26 + 32 * GET_64(s1, 36));

  // clear `from` bit
  s1 &= 18446744004990074863UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 18613632350953728UL) == 0);
  const bool capture = s2 & 18613632350953728UL;
  s2 &= 18428130441358597887UL;

  return capture;
}

// map entry 7940 (= 4 -> 31); note that
// `s1` must be the active player
static inline bool _do_move_4_31(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 31 + 32 * (blacks_turn || GET_64(s1, 36)));

  // clear `from` bit
  s1 &= 18446744004990074863UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 306844008569774336UL) == 0);
  const bool capture = s2 & 306844008569774336UL;
  s2 &= 18139900065139777279UL;

  return capture;
}

// map entry 261 (= 5 -> 1); note that
// `s1` must be the active player
static inline bool _do_move_5_1(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 1 + 32 * (!blacks_turn || GET_64(s1, 37)));

  // clear `from` bit
  s1 &= 18446743936270598111UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5 (= 5 -> 0); note that
// `s1` must be the active player
static inline bool _do_move_5_0(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 0 + 32 * (!blacks_turn || GET_64(s1, 37)));

  // clear `from` bit
  s1 &= 18446743936270598111UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2053 (= 5 -> 8); note that
// `s1` must be the active player
static inline bool _do_move_5_8(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 8 + 32 * GET_64(s1, 37));

  // clear `from` bit
  s1 &= 18446743936270598111UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3077 (= 5 -> 12); note that
// `s1` must be the active player
static inline bool _do_move_5_12(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 12 + 32 * GET_64(s1, 37));

  // clear `from` bit
  s1 &= 18446743936270598111UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1099511628032UL) == 0);
  const bool capture = s2 & 1099511628032UL;
  s2 &= 18446742974197923583UL;

  return capture;
}

// map entry 2309 (= 5 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_5_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 37));

  // clear `from` bit
  s1 &= 18446743936270598111UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3589 (= 5 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_5_14(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 37));

  // clear `from` bit
  s1 &= 18446743936270598111UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 2199023256064UL) == 0);
  const bool capture = s2 & 2199023256064UL;
  s2 &= 18446741874686295551UL;

  return capture;
}

// map entry 4613 (= 5 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_5_18(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 37));

  // clear `from` bit
  s1 &= 18446743936270598111UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 72567767450112UL) == 0);
  const bool capture = s2 & 72567767450112UL;
  s2 &= 18446671505942101503UL;

  return capture;
}

// map entry 5893 (= 5 -> 23); note that
// `s1` must be the active player
static inline bool _do_move_5_23(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 23 + 32 * GET_64(s1, 37));

  // clear `from` bit
  s1 &= 18446743936270598111UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1198467674554880UL) == 0);
  const bool capture = s2 & 1198467674554880UL;
  s2 &= 18445545606034996735UL;

  return capture;
}

// map entry 6917 (= 5 -> 27); note that
// `s1` must be the active player
static inline bool _do_move_5_27(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 27 + 32 * GET_64(s1, 37));

  // clear `from` bit
  s1 &= 18446743936270598111UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37227264701907456UL) == 0);
  const bool capture = s2 & 37227264701907456UL;
  s2 &= 18409516809007644159UL;

  return capture;
}

// map entry 518 (= 6 -> 2); note that
// `s1` must be the active player
static inline bool _do_move_6_2(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 2 + 32 * (!blacks_turn || GET_64(s1, 38)));

  // clear `from` bit
  s1 &= 18446743798831644607UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 262 (= 6 -> 1); note that
// `s1` must be the active player
static inline bool _do_move_6_1(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 1 + 32 * (!blacks_turn || GET_64(s1, 38)));

  // clear `from` bit
  s1 &= 18446743798831644607UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2310 (= 6 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_6_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 38));

  // clear `from` bit
  s1 &= 18446743798831644607UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3334 (= 6 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_6_13(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 38));

  // clear `from` bit
  s1 &= 18446743798831644607UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 2199023256064UL) == 0);
  const bool capture = s2 & 2199023256064UL;
  s2 &= 18446741874686295551UL;

  return capture;
}

// map entry 4102 (= 6 -> 16); note that
// `s1` must be the active player
static inline bool _do_move_6_16(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 16 + 32 * GET_64(s1, 38));

  // clear `from` bit
  s1 &= 18446743798831644607UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37383395353088UL) == 0);
  const bool capture = s2 & 37383395353088UL;
  s2 &= 18446706690314198527UL;

  return capture;
}

// map entry 5126 (= 6 -> 20); note that
// `s1` must be the active player
static inline bool _do_move_6_20(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 20 + 32 * GET_64(s1, 38));

  // clear `from` bit
  s1 &= 18446743798831644607UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 318858372129280UL) == 0);
  const bool capture = s2 & 318858372129280UL;
  s2 &= 18446425215337422335UL;

  return capture;
}

// map entry 2566 (= 6 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_6_10(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 38));

  // clear `from` bit
  s1 &= 18446743798831644607UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3846 (= 6 -> 15); note that
// `s1` must be the active player
static inline bool _do_move_6_15(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 15 + 32 * GET_64(s1, 38));

  // clear `from` bit
  s1 &= 18446743798831644607UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 4398046512128UL) == 0);
  const bool capture = s2 & 4398046512128UL;
  s2 &= 18446739675663039487UL;

  return capture;
}

// map entry 4870 (= 6 -> 19); note that
// `s1` must be the active player
static inline bool _do_move_6_19(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 19 + 32 * GET_64(s1, 38));

  // clear `from` bit
  s1 &= 18446743798831644607UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 145135534900224UL) == 0);
  const bool capture = s2 & 145135534900224UL;
  s2 &= 18446598938174651391UL;

  return capture;
}

// map entry 775 (= 7 -> 3); note that
// `s1` must be the active player
static inline bool _do_move_7_3(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 3 + 32 * (!blacks_turn || GET_64(s1, 39)));

  // clear `from` bit
  s1 &= 18446743523953737599UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 519 (= 7 -> 2); note that
// `s1` must be the active player
static inline bool _do_move_7_2(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 2 + 32 * (!blacks_turn || GET_64(s1, 39)));

  // clear `from` bit
  s1 &= 18446743523953737599UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2567 (= 7 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_7_10(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 39));

  // clear `from` bit
  s1 &= 18446743523953737599UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3591 (= 7 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_7_14(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 39));

  // clear `from` bit
  s1 &= 18446743523953737599UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 4398046512128UL) == 0);
  const bool capture = s2 & 4398046512128UL;
  s2 &= 18446739675663039487UL;

  return capture;
}

// map entry 4359 (= 7 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_7_17(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 39));

  // clear `from` bit
  s1 &= 18446743523953737599UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 74766790706176UL) == 0);
  const bool capture = s2 & 74766790706176UL;
  s2 &= 18446669306918845439UL;

  return capture;
}

// map entry 5383 (= 7 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_7_21(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 39));

  // clear `from` bit
  s1 &= 18446743523953737599UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 637716744258560UL) == 0);
  const bool capture = s2 & 637716744258560UL;
  s2 &= 18446106356965293055UL;

  return capture;
}

// map entry 6151 (= 7 -> 24); note that
// `s1` must be the active player
static inline bool _do_move_7_24(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 24 + 32 * GET_64(s1, 39));

  // clear `from` bit
  s1 &= 18446743523953737599UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9644916001096704UL) == 0);
  const bool capture = s2 & 9644916001096704UL;
  s2 &= 18437099157708454911UL;

  return capture;
}

// map entry 7175 (= 7 -> 28); note that
// `s1` must be the active player
static inline bool _do_move_7_28(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 28 + 32 * (blacks_turn || GET_64(s1, 39)));

  // clear `from` bit
  s1 &= 18446743523953737599UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 81702510055801856UL) == 0);
  const bool capture = s2 & 81702510055801856UL;
  s2 &= 18365041563653749759UL;

  return capture;
}

// map entry 2823 (= 7 -> 11); note that
// `s1` must be the active player
static inline bool _do_move_7_11(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 11 + 32 * GET_64(s1, 39));

  // clear `from` bit
  s1 &= 18446743523953737599UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 1288 (= 8 -> 5); note that
// `s1` must be the active player
static inline bool _do_move_8_5(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 5 + 32 * GET_64(s1, 40));

  // clear `from` bit
  s1 &= 18446742974197923583UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 264 (= 8 -> 1); note that
// `s1` must be the active player
static inline bool _do_move_8_1(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 1 + 32 * (!blacks_turn || GET_64(s1, 40)));

  // clear `from` bit
  s1 &= 18446742974197923583UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 137438953504UL) == 0);
  const bool capture = s2 & 137438953504UL;
  s2 &= 18446743936270598111UL;

  return capture;
}

// map entry 1032 (= 8 -> 4); note that
// `s1` must be the active player
static inline bool _do_move_8_4(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 4 + 32 * GET_64(s1, 40));

  // clear `from` bit
  s1 &= 18446742974197923583UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3080 (= 8 -> 12); note that
// `s1` must be the active player
static inline bool _do_move_8_12(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 12 + 32 * GET_64(s1, 40));

  // clear `from` bit
  s1 &= 18446742974197923583UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3336 (= 8 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_8_13(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 40));

  // clear `from` bit
  s1 &= 18446742974197923583UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4360 (= 8 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_8_17(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 40));

  // clear `from` bit
  s1 &= 18446742974197923583UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 35184372097024UL) == 0);
  const bool capture = s2 & 35184372097024UL;
  s2 &= 18446708889337454591UL;

  return capture;
}

// map entry 5640 (= 8 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_8_22(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 40));

  // clear `from` bit
  s1 &= 18446742974197923583UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 598134325649408UL) == 0);
  const bool capture = s2 & 598134325649408UL;
  s2 &= 18446145939383902207UL;

  return capture;
}

// map entry 6664 (= 8 -> 26); note that
// `s1` must be the active player
static inline bool _do_move_8_26(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 26 + 32 * GET_64(s1, 40));

  // clear `from` bit
  s1 &= 18446742974197923583UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 18612532839325696UL) == 0);
  const bool capture = s2 & 18612532839325696UL;
  s2 &= 18428131540870225919UL;

  return capture;
}

// map entry 7944 (= 8 -> 31); note that
// `s1` must be the active player
static inline bool _do_move_8_31(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 31 + 32 * (blacks_turn || GET_64(s1, 40)));

  // clear `from` bit
  s1 &= 18446742974197923583UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 306842909058146304UL) == 0);
  const bool capture = s2 & 306842909058146304UL;
  s2 &= 18139901164651405311UL;

  return capture;
}

// map entry 1545 (= 9 -> 6); note that
// `s1` must be the active player
static inline bool _do_move_9_6(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 6 + 32 * GET_64(s1, 41));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 521 (= 9 -> 2); note that
// `s1` must be the active player
static inline bool _do_move_9_2(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 2 + 32 * (!blacks_turn || GET_64(s1, 41)));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 274877907008UL) == 0);
  const bool capture = s2 & 274877907008UL;
  s2 &= 18446743798831644607UL;

  return capture;
}

// map entry 1289 (= 9 -> 5); note that
// `s1` must be the active player
static inline bool _do_move_9_5(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 5 + 32 * GET_64(s1, 41));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 9 (= 9 -> 0); note that
// `s1` must be the active player
static inline bool _do_move_9_0(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 0 + 32 * (!blacks_turn || GET_64(s1, 41)));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 137438953504UL) == 0);
  const bool capture = s2 & 137438953504UL;
  s2 &= 18446743936270598111UL;

  return capture;
}

// map entry 3337 (= 9 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_9_13(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 41));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4105 (= 9 -> 16); note that
// `s1` must be the active player
static inline bool _do_move_9_16(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 16 + 32 * GET_64(s1, 41));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 35184372097024UL) == 0);
  const bool capture = s2 & 35184372097024UL;
  s2 &= 18446708889337454591UL;

  return capture;
}

// map entry 5129 (= 9 -> 20); note that
// `s1` must be the active player
static inline bool _do_move_9_20(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 20 + 32 * GET_64(s1, 41));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 316659348873216UL) == 0);
  const bool capture = s2 & 316659348873216UL;
  s2 &= 18446427414360678399UL;

  return capture;
}

// map entry 3593 (= 9 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_9_14(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 41));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4617 (= 9 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_9_18(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 41));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 70368744194048UL) == 0);
  const bool capture = s2 & 70368744194048UL;
  s2 &= 18446673704965357567UL;

  return capture;
}

// map entry 5897 (= 9 -> 23); note that
// `s1` must be the active player
static inline bool _do_move_9_23(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 23 + 32 * GET_64(s1, 41));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1196268651298816UL) == 0);
  const bool capture = s2 & 1196268651298816UL;
  s2 &= 18445547805058252799UL;

  return capture;
}

// map entry 6921 (= 9 -> 27); note that
// `s1` must be the active player
static inline bool _do_move_9_27(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 27 + 32 * GET_64(s1, 41));

  // clear `from` bit
  s1 &= 18446741874686295551UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37225065678651392UL) == 0);
  const bool capture = s2 & 37225065678651392UL;
  s2 &= 18409519008030900223UL;

  return capture;
}

// map entry 1802 (= 10 -> 7); note that
// `s1` must be the active player
static inline bool _do_move_10_7(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 7 + 32 * GET_64(s1, 42));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 778 (= 10 -> 3); note that
// `s1` must be the active player
static inline bool _do_move_10_3(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 3 + 32 * (!blacks_turn || GET_64(s1, 42)));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 549755814016UL) == 0);
  const bool capture = s2 & 549755814016UL;
  s2 &= 18446743523953737599UL;

  return capture;
}

// map entry 1546 (= 10 -> 6); note that
// `s1` must be the active player
static inline bool _do_move_10_6(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 6 + 32 * GET_64(s1, 42));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 266 (= 10 -> 1); note that
// `s1` must be the active player
static inline bool _do_move_10_1(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 1 + 32 * (!blacks_turn || GET_64(s1, 42)));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 274877907008UL) == 0);
  const bool capture = s2 & 274877907008UL;
  s2 &= 18446743798831644607UL;

  return capture;
}

// map entry 3594 (= 10 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_10_14(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 42));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4362 (= 10 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_10_17(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 42));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 70368744194048UL) == 0);
  const bool capture = s2 & 70368744194048UL;
  s2 &= 18446673704965357567UL;

  return capture;
}

// map entry 5386 (= 10 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_10_21(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 42));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 633318697746432UL) == 0);
  const bool capture = s2 & 633318697746432UL;
  s2 &= 18446110755011805183UL;

  return capture;
}

// map entry 6154 (= 10 -> 24); note that
// `s1` must be the active player
static inline bool _do_move_10_24(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 24 + 32 * GET_64(s1, 42));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9640517954584576UL) == 0);
  const bool capture = s2 & 9640517954584576UL;
  s2 &= 18437103555754967039UL;

  return capture;
}

// map entry 7178 (= 10 -> 28); note that
// `s1` must be the active player
static inline bool _do_move_10_28(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 28 + 32 * (blacks_turn || GET_64(s1, 42)));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 81698112009289728UL) == 0);
  const bool capture = s2 & 81698112009289728UL;
  s2 &= 18365045961700261887UL;

  return capture;
}

// map entry 3850 (= 10 -> 15); note that
// `s1` must be the active player
static inline bool _do_move_10_15(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 15 + 32 * GET_64(s1, 42));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4874 (= 10 -> 19); note that
// `s1` must be the active player
static inline bool _do_move_10_19(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 19 + 32 * GET_64(s1, 42));

  // clear `from` bit
  s1 &= 18446739675663039487UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 140737488388096UL) == 0);
  const bool capture = s2 & 140737488388096UL;
  s2 &= 18446603336221163519UL;

  return capture;
}

// map entry 1803 (= 11 -> 7); note that
// `s1` must be the active player
static inline bool _do_move_11_7(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 7 + 32 * GET_64(s1, 43));

  // clear `from` bit
  s1 &= 18446735277616527359UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 523 (= 11 -> 2); note that
// `s1` must be the active player
static inline bool _do_move_11_2(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 2 + 32 * (!blacks_turn || GET_64(s1, 43)));

  // clear `from` bit
  s1 &= 18446735277616527359UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 549755814016UL) == 0);
  const bool capture = s2 & 549755814016UL;
  s2 &= 18446743523953737599UL;

  return capture;
}

// map entry 3851 (= 11 -> 15); note that
// `s1` must be the active player
static inline bool _do_move_11_15(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 15 + 32 * GET_64(s1, 43));

  // clear `from` bit
  s1 &= 18446735277616527359UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4619 (= 11 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_11_18(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 43));

  // clear `from` bit
  s1 &= 18446735277616527359UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 140737488388096UL) == 0);
  const bool capture = s2 & 140737488388096UL;
  s2 &= 18446603336221163519UL;

  return capture;
}

// map entry 5643 (= 11 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_11_22(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 43));

  // clear `from` bit
  s1 &= 18446735277616527359UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1266637395492864UL) == 0);
  const bool capture = s2 & 1266637395492864UL;
  s2 &= 18445477436314058751UL;

  return capture;
}

// map entry 6411 (= 11 -> 25); note that
// `s1` must be the active player
static inline bool _do_move_11_25(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 25 + 32 * GET_64(s1, 43));

  // clear `from` bit
  s1 &= 18446735277616527359UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 19281035909169152UL) == 0);
  const bool capture = s2 & 19281035909169152UL;
  s2 &= 18427463037800382463UL;

  return capture;
}

// map entry 7435 (= 11 -> 29); note that
// `s1` must be the active player
static inline bool _do_move_11_29(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 29 + 32 * (blacks_turn || GET_64(s1, 43)));

  // clear `from` bit
  s1 &= 18446735277616527359UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 163396224018579456UL) == 0);
  const bool capture = s2 & 163396224018579456UL;
  s2 &= 18283347849690972159UL;

  return capture;
}

// map entry 2060 (= 12 -> 8); note that
// `s1` must be the active player
static inline bool _do_move_12_8(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 8 + 32 * GET_64(s1, 44));

  // clear `from` bit
  s1 &= 18446726481523503103UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 1292 (= 12 -> 5); note that
// `s1` must be the active player
static inline bool _do_move_12_5(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 5 + 32 * GET_64(s1, 44));

  // clear `from` bit
  s1 &= 18446726481523503103UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1099511628032UL) == 0);
  const bool capture = s2 & 1099511628032UL;
  s2 &= 18446742974197923583UL;

  return capture;
}

// map entry 268 (= 12 -> 1); note that
// `s1` must be the active player
static inline bool _do_move_12_1(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 1 + 32 * (!blacks_turn || GET_64(s1, 44)));

  // clear `from` bit
  s1 &= 18446726481523503103UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1236950581536UL) == 0);
  const bool capture = s2 & 1236950581536UL;
  s2 &= 18446742836758970079UL;

  return capture;
}

// map entry 4108 (= 12 -> 16); note that
// `s1` must be the active player
static inline bool _do_move_12_16(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 16 + 32 * GET_64(s1, 44));

  // clear `from` bit
  s1 &= 18446726481523503103UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5388 (= 12 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_12_21(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 44));

  // clear `from` bit
  s1 &= 18446726481523503103UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 281474976776192UL) == 0);
  const bool capture = s2 & 281474976776192UL;
  s2 &= 18446462598732775423UL;

  return capture;
}

// map entry 6412 (= 12 -> 25); note that
// `s1` must be the active player
static inline bool _do_move_12_25(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 25 + 32 * GET_64(s1, 44));

  // clear `from` bit
  s1 &= 18446726481523503103UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9288674233614336UL) == 0);
  const bool capture = s2 & 9288674233614336UL;
  s2 &= 18437455399475937279UL;

  return capture;
}

// map entry 7692 (= 12 -> 30); note that
// `s1` must be the active player
static inline bool _do_move_12_30(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 30 + 32 * (blacks_turn || GET_64(s1, 44)));

  // clear `from` bit
  s1 &= 18446726481523503103UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 153403862343024640UL) == 0);
  const bool capture = s2 & 153403862343024640UL;
  s2 &= 18293340211366526975UL;

  return capture;
}

// map entry 2317 (= 13 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_13_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 45));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 1549 (= 13 -> 6); note that
// `s1` must be the active player
static inline bool _do_move_13_6(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 6 + 32 * GET_64(s1, 45));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 2199023256064UL) == 0);
  const bool capture = s2 & 2199023256064UL;
  s2 &= 18446741874686295551UL;

  return capture;
}

// map entry 525 (= 13 -> 2); note that
// `s1` must be the active player
static inline bool _do_move_13_2(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 2 + 32 * (!blacks_turn || GET_64(s1, 45)));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 2473901163072UL) == 0);
  const bool capture = s2 & 2473901163072UL;
  s2 &= 18446741599808388543UL;

  return capture;
}

// map entry 2061 (= 13 -> 8); note that
// `s1` must be the active player
static inline bool _do_move_13_8(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 8 + 32 * GET_64(s1, 45));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 1037 (= 13 -> 4); note that
// `s1` must be the active player
static inline bool _do_move_13_4(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 4 + 32 * GET_64(s1, 45));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1099511628032UL) == 0);
  const bool capture = s2 & 1099511628032UL;
  s2 &= 18446742974197923583UL;

  return capture;
}

// map entry 4109 (= 13 -> 16); note that
// `s1` must be the active player
static inline bool _do_move_13_16(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 16 + 32 * GET_64(s1, 45));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5133 (= 13 -> 20); note that
// `s1` must be the active player
static inline bool _do_move_13_20(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 20 + 32 * GET_64(s1, 45));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 281474976776192UL) == 0);
  const bool capture = s2 & 281474976776192UL;
  s2 &= 18446462598732775423UL;

  return capture;
}

// map entry 4365 (= 13 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_13_17(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 45));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5645 (= 13 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_13_22(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 45));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 562949953552384UL) == 0);
  const bool capture = s2 & 562949953552384UL;
  s2 &= 18446181123755999231UL;

  return capture;
}

// map entry 6669 (= 13 -> 26); note that
// `s1` must be the active player
static inline bool _do_move_13_26(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 26 + 32 * GET_64(s1, 45));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 18577348467228672UL) == 0);
  const bool capture = s2 & 18577348467228672UL;
  s2 &= 18428166725242322943UL;

  return capture;
}

// map entry 7949 (= 13 -> 31); note that
// `s1` must be the active player
static inline bool _do_move_13_31(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 31 + 32 * (blacks_turn || GET_64(s1, 45)));

  // clear `from` bit
  s1 &= 18446708889337454591UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 306807724686049280UL) == 0);
  const bool capture = s2 & 306807724686049280UL;
  s2 &= 18139936349023502335UL;

  return capture;
}

// map entry 2574 (= 14 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_14_10(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 46));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 1806 (= 14 -> 7); note that
// `s1` must be the active player
static inline bool _do_move_14_7(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 7 + 32 * GET_64(s1, 46));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 4398046512128UL) == 0);
  const bool capture = s2 & 4398046512128UL;
  s2 &= 18446739675663039487UL;

  return capture;
}

// map entry 782 (= 14 -> 3); note that
// `s1` must be the active player
static inline bool _do_move_14_3(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 3 + 32 * (!blacks_turn || GET_64(s1, 46)));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 4947802326144UL) == 0);
  const bool capture = s2 & 4947802326144UL;
  s2 &= 18446739125907225471UL;

  return capture;
}

// map entry 2318 (= 14 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_14_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 46));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 1294 (= 14 -> 5); note that
// `s1` must be the active player
static inline bool _do_move_14_5(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 5 + 32 * GET_64(s1, 46));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 2199023256064UL) == 0);
  const bool capture = s2 & 2199023256064UL;
  s2 &= 18446741874686295551UL;

  return capture;
}

// map entry 14 (= 14 -> 0); note that
// `s1` must be the active player
static inline bool _do_move_14_0(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 0 + 32 * (!blacks_turn || GET_64(s1, 46)));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 2336462209568UL) == 0);
  const bool capture = s2 & 2336462209568UL;
  s2 &= 18446741737247342047UL;

  return capture;
}

// map entry 4366 (= 14 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_14_17(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 46));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5390 (= 14 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_14_21(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 46));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 562949953552384UL) == 0);
  const bool capture = s2 & 562949953552384UL;
  s2 &= 18446181123755999231UL;

  return capture;
}

// map entry 6158 (= 14 -> 24); note that
// `s1` must be the active player
static inline bool _do_move_14_24(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 24 + 32 * GET_64(s1, 46));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9570149210390528UL) == 0);
  const bool capture = s2 & 9570149210390528UL;
  s2 &= 18437173924499161087UL;

  return capture;
}

// map entry 7182 (= 14 -> 28); note that
// `s1` must be the active player
static inline bool _do_move_14_28(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 28 + 32 * (blacks_turn || GET_64(s1, 46)));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 81627743265095680UL) == 0);
  const bool capture = s2 & 81627743265095680UL;
  s2 &= 18365116330444455935UL;

  return capture;
}

// map entry 4622 (= 14 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_14_18(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 46));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5902 (= 14 -> 23); note that
// `s1` must be the active player
static inline bool _do_move_14_23(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 23 + 32 * GET_64(s1, 46));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1125899907104768UL) == 0);
  const bool capture = s2 & 1125899907104768UL;
  s2 &= 18445618173802446847UL;

  return capture;
}

// map entry 6926 (= 14 -> 27); note that
// `s1` must be the active player
static inline bool _do_move_14_27(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 27 + 32 * GET_64(s1, 46));

  // clear `from` bit
  s1 &= 18446673704965357567UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37154696934457344UL) == 0);
  const bool capture = s2 & 37154696934457344UL;
  s2 &= 18409589376775094271UL;

  return capture;
}

// map entry 2831 (= 15 -> 11); note that
// `s1` must be the active player
static inline bool _do_move_15_11(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 11 + 32 * GET_64(s1, 47));

  // clear `from` bit
  s1 &= 18446603336221163519UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2575 (= 15 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_15_10(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 47));

  // clear `from` bit
  s1 &= 18446603336221163519UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 1551 (= 15 -> 6); note that
// `s1` must be the active player
static inline bool _do_move_15_6(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 6 + 32 * GET_64(s1, 47));

  // clear `from` bit
  s1 &= 18446603336221163519UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 4398046512128UL) == 0);
  const bool capture = s2 & 4398046512128UL;
  s2 &= 18446739675663039487UL;

  return capture;
}

// map entry 271 (= 15 -> 1); note that
// `s1` must be the active player
static inline bool _do_move_15_1(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 1 + 32 * (!blacks_turn || GET_64(s1, 47)));

  // clear `from` bit
  s1 &= 18446603336221163519UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 4672924419136UL) == 0);
  const bool capture = s2 & 4672924419136UL;
  s2 &= 18446739400785132479UL;

  return capture;
}

// map entry 4623 (= 15 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_15_18(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 47));

  // clear `from` bit
  s1 &= 18446603336221163519UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5647 (= 15 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_15_22(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 47));

  // clear `from` bit
  s1 &= 18446603336221163519UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1125899907104768UL) == 0);
  const bool capture = s2 & 1125899907104768UL;
  s2 &= 18445618173802446847UL;

  return capture;
}

// map entry 6415 (= 15 -> 25); note that
// `s1` must be the active player
static inline bool _do_move_15_25(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 25 + 32 * GET_64(s1, 47));

  // clear `from` bit
  s1 &= 18446603336221163519UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 19140298420781056UL) == 0);
  const bool capture = s2 & 19140298420781056UL;
  s2 &= 18427603775288770559UL;

  return capture;
}

// map entry 7439 (= 15 -> 29); note that
// `s1` must be the active player
static inline bool _do_move_15_29(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 29 + 32 * (blacks_turn || GET_64(s1, 47)));

  // clear `from` bit
  s1 &= 18446603336221163519UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 163255486530191360UL) == 0);
  const bool capture = s2 & 163255486530191360UL;
  s2 &= 18283488587179360255UL;

  return capture;
}

// map entry 4879 (= 15 -> 19); note that
// `s1` must be the active player
static inline bool _do_move_15_19(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 19 + 32 * GET_64(s1, 47));

  // clear `from` bit
  s1 &= 18446603336221163519UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3344 (= 16 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_16_13(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 48));

  // clear `from` bit
  s1 &= 18446462598732775423UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2320 (= 16 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_16_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 48));

  // clear `from` bit
  s1 &= 18446462598732775423UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 35184372097024UL) == 0);
  const bool capture = s2 & 35184372097024UL;
  s2 &= 18446708889337454591UL;

  return capture;
}

// map entry 1552 (= 16 -> 6); note that
// `s1` must be the active player
static inline bool _do_move_16_6(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 6 + 32 * GET_64(s1, 48));

  // clear `from` bit
  s1 &= 18446462598732775423UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37383395353088UL) == 0);
  const bool capture = s2 & 37383395353088UL;
  s2 &= 18446706690314198527UL;

  return capture;
}

// map entry 528 (= 16 -> 2); note that
// `s1` must be the active player
static inline bool _do_move_16_2(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 2 + 32 * (!blacks_turn || GET_64(s1, 48)));

  // clear `from` bit
  s1 &= 18446462598732775423UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37658273260096UL) == 0);
  const bool capture = s2 & 37658273260096UL;
  s2 &= 18446706415436291519UL;

  return capture;
}

// map entry 3088 (= 16 -> 12); note that
// `s1` must be the active player
static inline bool _do_move_16_12(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 12 + 32 * GET_64(s1, 48));

  // clear `from` bit
  s1 &= 18446462598732775423UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5136 (= 16 -> 20); note that
// `s1` must be the active player
static inline bool _do_move_16_20(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 20 + 32 * GET_64(s1, 48));

  // clear `from` bit
  s1 &= 18446462598732775423UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5392 (= 16 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_16_21(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 48));

  // clear `from` bit
  s1 &= 18446462598732775423UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 6416 (= 16 -> 25); note that
// `s1` must be the active player
static inline bool _do_move_16_25(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 25 + 32 * GET_64(s1, 48));

  // clear `from` bit
  s1 &= 18446462598732775423UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9007199256838144UL) == 0);
  const bool capture = s2 & 9007199256838144UL;
  s2 &= 18437736874452713471UL;

  return capture;
}

// map entry 7696 (= 16 -> 30); note that
// `s1` must be the active player
static inline bool _do_move_16_30(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 30 + 32 * (blacks_turn || GET_64(s1, 48)));

  // clear `from` bit
  s1 &= 18446462598732775423UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 153122387366248448UL) == 0);
  const bool capture = s2 & 153122387366248448UL;
  s2 &= 18293621686343303167UL;

  return capture;
}

// map entry 3601 (= 17 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_17_14(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 49));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2577 (= 17 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_17_10(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 49));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 70368744194048UL) == 0);
  const bool capture = s2 & 70368744194048UL;
  s2 &= 18446673704965357567UL;

  return capture;
}

// map entry 1809 (= 17 -> 7); note that
// `s1` must be the active player
static inline bool _do_move_17_7(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 7 + 32 * GET_64(s1, 49));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 74766790706176UL) == 0);
  const bool capture = s2 & 74766790706176UL;
  s2 &= 18446669306918845439UL;

  return capture;
}

// map entry 785 (= 17 -> 3); note that
// `s1` must be the active player
static inline bool _do_move_17_3(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 3 + 32 * (!blacks_turn || GET_64(s1, 49)));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 75316546520192UL) == 0);
  const bool capture = s2 & 75316546520192UL;
  s2 &= 18446668757163031423UL;

  return capture;
}

// map entry 3345 (= 17 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_17_13(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 49));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2065 (= 17 -> 8); note that
// `s1` must be the active player
static inline bool _do_move_17_8(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 8 + 32 * GET_64(s1, 49));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 35184372097024UL) == 0);
  const bool capture = s2 & 35184372097024UL;
  s2 &= 18446708889337454591UL;

  return capture;
}

// map entry 1041 (= 17 -> 4); note that
// `s1` must be the active player
static inline bool _do_move_17_4(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 4 + 32 * GET_64(s1, 49));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 36283883725056UL) == 0);
  const bool capture = s2 & 36283883725056UL;
  s2 &= 18446707789825826559UL;

  return capture;
}

// map entry 5393 (= 17 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_17_21(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 49));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 6161 (= 17 -> 24); note that
// `s1` must be the active player
static inline bool _do_move_17_24(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 24 + 32 * GET_64(s1, 49));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9007199256838144UL) == 0);
  const bool capture = s2 & 9007199256838144UL;
  s2 &= 18437736874452713471UL;

  return capture;
}

// map entry 7185 (= 17 -> 28); note that
// `s1` must be the active player
static inline bool _do_move_17_28(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 28 + 32 * (blacks_turn || GET_64(s1, 49)));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 81064793311543296UL) == 0);
  const bool capture = s2 & 81064793311543296UL;
  s2 &= 18365679280398008319UL;

  return capture;
}

// map entry 5649 (= 17 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_17_22(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 49));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 6673 (= 17 -> 26); note that
// `s1` must be the active player
static inline bool _do_move_17_26(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 26 + 32 * GET_64(s1, 49));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 18014398513676288UL) == 0);
  const bool capture = s2 & 18014398513676288UL;
  s2 &= 18428729675195875327UL;

  return capture;
}

// map entry 7953 (= 17 -> 31); note that
// `s1` must be the active player
static inline bool _do_move_17_31(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 31 + 32 * (blacks_turn || GET_64(s1, 49)));

  // clear `from` bit
  s1 &= 18446181123755999231UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 306244774732496896UL) == 0);
  const bool capture = s2 & 306244774732496896UL;
  s2 &= 18140499298977054719UL;

  return capture;
}

// map entry 3858 (= 18 -> 15); note that
// `s1` must be the active player
static inline bool _do_move_18_15(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 15 + 32 * GET_64(s1, 50));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2834 (= 18 -> 11); note that
// `s1` must be the active player
static inline bool _do_move_18_11(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 11 + 32 * GET_64(s1, 50));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 140737488388096UL) == 0);
  const bool capture = s2 & 140737488388096UL;
  s2 &= 18446603336221163519UL;

  return capture;
}

// map entry 3602 (= 18 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_18_14(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 50));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2322 (= 18 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_18_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 50));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 70368744194048UL) == 0);
  const bool capture = s2 & 70368744194048UL;
  s2 &= 18446673704965357567UL;

  return capture;
}

// map entry 1298 (= 18 -> 5); note that
// `s1` must be the active player
static inline bool _do_move_18_5(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 5 + 32 * GET_64(s1, 50));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 72567767450112UL) == 0);
  const bool capture = s2 & 72567767450112UL;
  s2 &= 18446671505942101503UL;

  return capture;
}

// map entry 18 (= 18 -> 0); note that
// `s1` must be the active player
static inline bool _do_move_18_0(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 0 + 32 * (!blacks_turn || GET_64(s1, 50)));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 72705206403616UL) == 0);
  const bool capture = s2 & 72705206403616UL;
  s2 &= 18446671368503147999UL;

  return capture;
}

// map entry 5650 (= 18 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_18_22(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 50));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 6418 (= 18 -> 25); note that
// `s1` must be the active player
static inline bool _do_move_18_25(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 25 + 32 * GET_64(s1, 50));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 18014398513676288UL) == 0);
  const bool capture = s2 & 18014398513676288UL;
  s2 &= 18428729675195875327UL;

  return capture;
}

// map entry 7442 (= 18 -> 29); note that
// `s1` must be the active player
static inline bool _do_move_18_29(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 29 + 32 * (blacks_turn || GET_64(s1, 50)));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 162129586623086592UL) == 0);
  const bool capture = s2 & 162129586623086592UL;
  s2 &= 18284614487086465023UL;

  return capture;
}

// map entry 5906 (= 18 -> 23); note that
// `s1` must be the active player
static inline bool _do_move_18_23(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 23 + 32 * GET_64(s1, 50));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 6930 (= 18 -> 27); note that
// `s1` must be the active player
static inline bool _do_move_18_27(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 27 + 32 * GET_64(s1, 50));

  // clear `from` bit
  s1 &= 18445618173802446847UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 36028797027352576UL) == 0);
  const bool capture = s2 & 36028797027352576UL;
  s2 &= 18410715276682199039UL;

  return capture;
}

// map entry 3859 (= 19 -> 15); note that
// `s1` must be the active player
static inline bool _do_move_19_15(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 15 + 32 * GET_64(s1, 51));

  // clear `from` bit
  s1 &= 18444492273895342079UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 2579 (= 19 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_19_10(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 51));

  // clear `from` bit
  s1 &= 18444492273895342079UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 140737488388096UL) == 0);
  const bool capture = s2 & 140737488388096UL;
  s2 &= 18446603336221163519UL;

  return capture;
}

// map entry 1555 (= 19 -> 6); note that
// `s1` must be the active player
static inline bool _do_move_19_6(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 6 + 32 * GET_64(s1, 51));

  // clear `from` bit
  s1 &= 18444492273895342079UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 145135534900224UL) == 0);
  const bool capture = s2 & 145135534900224UL;
  s2 &= 18446598938174651391UL;

  return capture;
}

// map entry 275 (= 19 -> 1); note that
// `s1` must be the active player
static inline bool _do_move_19_1(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 1 + 32 * (!blacks_turn || GET_64(s1, 51)));

  // clear `from` bit
  s1 &= 18444492273895342079UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 145410412807232UL) == 0);
  const bool capture = s2 & 145410412807232UL;
  s2 &= 18446598663296744383UL;

  return capture;
}

// map entry 5907 (= 19 -> 23); note that
// `s1` must be the active player
static inline bool _do_move_19_23(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 23 + 32 * GET_64(s1, 51));

  // clear `from` bit
  s1 &= 18444492273895342079UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 6675 (= 19 -> 26); note that
// `s1` must be the active player
static inline bool _do_move_19_26(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 26 + 32 * GET_64(s1, 51));

  // clear `from` bit
  s1 &= 18444492273895342079UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 36028797027352576UL) == 0);
  const bool capture = s2 & 36028797027352576UL;
  s2 &= 18410715276682199039UL;

  return capture;
}

// map entry 7699 (= 19 -> 30); note that
// `s1` must be the active player
static inline bool _do_move_19_30(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 30 + 32 * (blacks_turn || GET_64(s1, 51)));

  // clear `from` bit
  s1 &= 18444492273895342079UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 324259173246173184UL) == 0);
  const bool capture = s2 & 324259173246173184UL;
  s2 &= 18122484900463378431UL;

  return capture;
}

// map entry 4116 (= 20 -> 16); note that
// `s1` must be the active player
static inline bool _do_move_20_16(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 16 + 32 * GET_64(s1, 52));

  // clear `from` bit
  s1 &= 18442240474081132543UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3348 (= 20 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_20_13(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 52));

  // clear `from` bit
  s1 &= 18442240474081132543UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 281474976776192UL) == 0);
  const bool capture = s2 & 281474976776192UL;
  s2 &= 18446462598732775423UL;

  return capture;
}

// map entry 2324 (= 20 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_20_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 52));

  // clear `from` bit
  s1 &= 18442240474081132543UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 316659348873216UL) == 0);
  const bool capture = s2 & 316659348873216UL;
  s2 &= 18446427414360678399UL;

  return capture;
}

// map entry 1556 (= 20 -> 6); note that
// `s1` must be the active player
static inline bool _do_move_20_6(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 6 + 32 * GET_64(s1, 52));

  // clear `from` bit
  s1 &= 18442240474081132543UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 318858372129280UL) == 0);
  const bool capture = s2 & 318858372129280UL;
  s2 &= 18446425215337422335UL;

  return capture;
}

// map entry 532 (= 20 -> 2); note that
// `s1` must be the active player
static inline bool _do_move_20_2(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 2 + 32 * (!blacks_turn || GET_64(s1, 52)));

  // clear `from` bit
  s1 &= 18442240474081132543UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 319133250036288UL) == 0);
  const bool capture = s2 & 319133250036288UL;
  s2 &= 18446424940459515327UL;

  return capture;
}

// map entry 6164 (= 20 -> 24); note that
// `s1` must be the active player
static inline bool _do_move_20_24(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 24 + 32 * GET_64(s1, 52));

  // clear `from` bit
  s1 &= 18442240474081132543UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 7444 (= 20 -> 29); note that
// `s1` must be the active player
static inline bool _do_move_20_29(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 29 + 32 * (blacks_turn || GET_64(s1, 52)));

  // clear `from` bit
  s1 &= 18442240474081132543UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 72057594054705152UL) == 0);
  const bool capture = s2 & 72057594054705152UL;
  s2 &= 18374686479654846463UL;

  return capture;
}

// map entry 4373 (= 21 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_21_17(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 53));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3605 (= 21 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_21_14(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 53));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 562949953552384UL) == 0);
  const bool capture = s2 & 562949953552384UL;
  s2 &= 18446181123755999231UL;

  return capture;
}

// map entry 2581 (= 21 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_21_10(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 53));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 633318697746432UL) == 0);
  const bool capture = s2 & 633318697746432UL;
  s2 &= 18446110755011805183UL;

  return capture;
}

// map entry 1813 (= 21 -> 7); note that
// `s1` must be the active player
static inline bool _do_move_21_7(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 7 + 32 * GET_64(s1, 53));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 637716744258560UL) == 0);
  const bool capture = s2 & 637716744258560UL;
  s2 &= 18446106356965293055UL;

  return capture;
}

// map entry 789 (= 21 -> 3); note that
// `s1` must be the active player
static inline bool _do_move_21_3(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 3 + 32 * (!blacks_turn || GET_64(s1, 53)));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 638266500072576UL) == 0);
  const bool capture = s2 & 638266500072576UL;
  s2 &= 18446105807209479039UL;

  return capture;
}

// map entry 4117 (= 21 -> 16); note that
// `s1` must be the active player
static inline bool _do_move_21_16(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 16 + 32 * GET_64(s1, 53));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3093 (= 21 -> 12); note that
// `s1` must be the active player
static inline bool _do_move_21_12(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 12 + 32 * GET_64(s1, 53));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 281474976776192UL) == 0);
  const bool capture = s2 & 281474976776192UL;
  s2 &= 18446462598732775423UL;

  return capture;
}

// map entry 6165 (= 21 -> 24); note that
// `s1` must be the active player
static inline bool _do_move_21_24(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 24 + 32 * GET_64(s1, 53));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 7189 (= 21 -> 28); note that
// `s1` must be the active player
static inline bool _do_move_21_28(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 28 + 32 * (blacks_turn || GET_64(s1, 53)));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 72057594054705152UL) == 0);
  const bool capture = s2 & 72057594054705152UL;
  s2 &= 18374686479654846463UL;

  return capture;
}

// map entry 6421 (= 21 -> 25); note that
// `s1` must be the active player
static inline bool _do_move_21_25(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 25 + 32 * GET_64(s1, 53));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 7701 (= 21 -> 30); note that
// `s1` must be the active player
static inline bool _do_move_21_30(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 30 + 32 * (blacks_turn || GET_64(s1, 53)));

  // clear `from` bit
  s1 &= 18437736874452713471UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 144115188109410304UL) == 0);
  const bool capture = s2 & 144115188109410304UL;
  s2 &= 18302628885600141311UL;

  return capture;
}

// map entry 4630 (= 22 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_22_18(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 54));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3862 (= 22 -> 15); note that
// `s1` must be the active player
static inline bool _do_move_22_15(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 15 + 32 * GET_64(s1, 54));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1125899907104768UL) == 0);
  const bool capture = s2 & 1125899907104768UL;
  s2 &= 18445618173802446847UL;

  return capture;
}

// map entry 2838 (= 22 -> 11); note that
// `s1` must be the active player
static inline bool _do_move_22_11(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 11 + 32 * GET_64(s1, 54));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1266637395492864UL) == 0);
  const bool capture = s2 & 1266637395492864UL;
  s2 &= 18445477436314058751UL;

  return capture;
}

// map entry 4374 (= 22 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_22_17(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 54));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3350 (= 22 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_22_13(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 54));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 562949953552384UL) == 0);
  const bool capture = s2 & 562949953552384UL;
  s2 &= 18446181123755999231UL;

  return capture;
}

// map entry 2070 (= 22 -> 8); note that
// `s1` must be the active player
static inline bool _do_move_22_8(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 8 + 32 * GET_64(s1, 54));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 598134325649408UL) == 0);
  const bool capture = s2 & 598134325649408UL;
  s2 &= 18446145939383902207UL;

  return capture;
}

// map entry 1046 (= 22 -> 4); note that
// `s1` must be the active player
static inline bool _do_move_22_4(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 4 + 32 * GET_64(s1, 54));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 599233837277440UL) == 0);
  const bool capture = s2 & 599233837277440UL;
  s2 &= 18446144839872274175UL;

  return capture;
}

// map entry 6422 (= 22 -> 25); note that
// `s1` must be the active player
static inline bool _do_move_22_25(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 25 + 32 * GET_64(s1, 54));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 7446 (= 22 -> 29); note that
// `s1` must be the active player
static inline bool _do_move_22_29(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 29 + 32 * (blacks_turn || GET_64(s1, 54)));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 144115188109410304UL) == 0);
  const bool capture = s2 & 144115188109410304UL;
  s2 &= 18302628885600141311UL;

  return capture;
}

// map entry 6678 (= 22 -> 26); note that
// `s1` must be the active player
static inline bool _do_move_22_26(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 26 + 32 * GET_64(s1, 54));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 7958 (= 22 -> 31); note that
// `s1` must be the active player
static inline bool _do_move_22_31(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 31 + 32 * (blacks_turn || GET_64(s1, 54)));

  // clear `from` bit
  s1 &= 18428729675195875327UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 288230376218820608UL) == 0);
  const bool capture = s2 & 288230376218820608UL;
  s2 &= 18158513697490731007UL;

  return capture;
}

// map entry 4887 (= 23 -> 19); note that
// `s1` must be the active player
static inline bool _do_move_23_19(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 19 + 32 * GET_64(s1, 55));

  // clear `from` bit
  s1 &= 18410715276682199039UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4631 (= 23 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_23_18(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 55));

  // clear `from` bit
  s1 &= 18410715276682199039UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 3607 (= 23 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_23_14(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 55));

  // clear `from` bit
  s1 &= 18410715276682199039UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1125899907104768UL) == 0);
  const bool capture = s2 & 1125899907104768UL;
  s2 &= 18445618173802446847UL;

  return capture;
}

// map entry 2327 (= 23 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_23_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 55));

  // clear `from` bit
  s1 &= 18410715276682199039UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1196268651298816UL) == 0);
  const bool capture = s2 & 1196268651298816UL;
  s2 &= 18445547805058252799UL;

  return capture;
}

// map entry 1303 (= 23 -> 5); note that
// `s1` must be the active player
static inline bool _do_move_23_5(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 5 + 32 * GET_64(s1, 55));

  // clear `from` bit
  s1 &= 18410715276682199039UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1198467674554880UL) == 0);
  const bool capture = s2 & 1198467674554880UL;
  s2 &= 18445545606034996735UL;

  return capture;
}

// map entry 23 (= 23 -> 0); note that
// `s1` must be the active player
static inline bool _do_move_23_0(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 0 + 32 * (!blacks_turn || GET_64(s1, 55)));

  // clear `from` bit
  s1 &= 18410715276682199039UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 1198605113508384UL) == 0);
  const bool capture = s2 & 1198605113508384UL;
  s2 &= 18445545468596043231UL;

  return capture;
}

// map entry 6679 (= 23 -> 26); note that
// `s1` must be the active player
static inline bool _do_move_23_26(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 26 + 32 * GET_64(s1, 55));

  // clear `from` bit
  s1 &= 18410715276682199039UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 7703 (= 23 -> 30); note that
// `s1` must be the active player
static inline bool _do_move_23_30(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 30 + 32 * (blacks_turn || GET_64(s1, 55)));

  // clear `from` bit
  s1 &= 18410715276682199039UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 288230376218820608UL) == 0);
  const bool capture = s2 & 288230376218820608UL;
  s2 &= 18158513697490731007UL;

  return capture;
}

// map entry 6935 (= 23 -> 27); note that
// `s1` must be the active player
static inline bool _do_move_23_27(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 27 + 32 * GET_64(s1, 55));

  // clear `from` bit
  s1 &= 18410715276682199039UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5400 (= 24 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_24_21(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 56));

  // clear `from` bit
  s1 &= 18374686479654846463UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4376 (= 24 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_24_17(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 56));

  // clear `from` bit
  s1 &= 18374686479654846463UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9007199256838144UL) == 0);
  const bool capture = s2 & 9007199256838144UL;
  s2 &= 18437736874452713471UL;

  return capture;
}

// map entry 3608 (= 24 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_24_14(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 56));

  // clear `from` bit
  s1 &= 18374686479654846463UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9570149210390528UL) == 0);
  const bool capture = s2 & 9570149210390528UL;
  s2 &= 18437173924499161087UL;

  return capture;
}

// map entry 2584 (= 24 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_24_10(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 56));

  // clear `from` bit
  s1 &= 18374686479654846463UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9640517954584576UL) == 0);
  const bool capture = s2 & 9640517954584576UL;
  s2 &= 18437103555754967039UL;

  return capture;
}

// map entry 1816 (= 24 -> 7); note that
// `s1` must be the active player
static inline bool _do_move_24_7(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 7 + 32 * GET_64(s1, 56));

  // clear `from` bit
  s1 &= 18374686479654846463UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9644916001096704UL) == 0);
  const bool capture = s2 & 9644916001096704UL;
  s2 &= 18437099157708454911UL;

  return capture;
}

// map entry 792 (= 24 -> 3); note that
// `s1` must be the active player
static inline bool _do_move_24_3(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 3 + 32 * (!blacks_turn || GET_64(s1, 56)));

  // clear `from` bit
  s1 &= 18374686479654846463UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9645465756910720UL) == 0);
  const bool capture = s2 & 9645465756910720UL;
  s2 &= 18437098607952640895UL;

  return capture;
}

// map entry 5144 (= 24 -> 20); note that
// `s1` must be the active player
static inline bool _do_move_24_20(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 20 + 32 * GET_64(s1, 56));

  // clear `from` bit
  s1 &= 18374686479654846463UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 7192 (= 24 -> 28); note that
// `s1` must be the active player
static inline bool _do_move_24_28(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 28 + 32 * (blacks_turn || GET_64(s1, 56)));

  // clear `from` bit
  s1 &= 18374686479654846463UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 7448 (= 24 -> 29); note that
// `s1` must be the active player
static inline bool _do_move_24_29(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 29 + 32 * (blacks_turn || GET_64(s1, 56)));

  // clear `from` bit
  s1 &= 18374686479654846463UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5657 (= 25 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_25_22(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 57));

  // clear `from` bit
  s1 &= 18302628885600141311UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4633 (= 25 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_25_18(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 57));

  // clear `from` bit
  s1 &= 18302628885600141311UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 18014398513676288UL) == 0);
  const bool capture = s2 & 18014398513676288UL;
  s2 &= 18428729675195875327UL;

  return capture;
}

// map entry 3865 (= 25 -> 15); note that
// `s1` must be the active player
static inline bool _do_move_25_15(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 15 + 32 * GET_64(s1, 57));

  // clear `from` bit
  s1 &= 18302628885600141311UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 19140298420781056UL) == 0);
  const bool capture = s2 & 19140298420781056UL;
  s2 &= 18427603775288770559UL;

  return capture;
}

// map entry 2841 (= 25 -> 11); note that
// `s1` must be the active player
static inline bool _do_move_25_11(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 11 + 32 * GET_64(s1, 57));

  // clear `from` bit
  s1 &= 18302628885600141311UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 19281035909169152UL) == 0);
  const bool capture = s2 & 19281035909169152UL;
  s2 &= 18427463037800382463UL;

  return capture;
}

// map entry 5401 (= 25 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_25_21(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 57));

  // clear `from` bit
  s1 &= 18302628885600141311UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4121 (= 25 -> 16); note that
// `s1` must be the active player
static inline bool _do_move_25_16(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 16 + 32 * GET_64(s1, 57));

  // clear `from` bit
  s1 &= 18302628885600141311UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9007199256838144UL) == 0);
  const bool capture = s2 & 9007199256838144UL;
  s2 &= 18437736874452713471UL;

  return capture;
}

// map entry 3097 (= 25 -> 12); note that
// `s1` must be the active player
static inline bool _do_move_25_12(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 12 + 32 * GET_64(s1, 57));

  // clear `from` bit
  s1 &= 18302628885600141311UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 9288674233614336UL) == 0);
  const bool capture = s2 & 9288674233614336UL;
  s2 &= 18437455399475937279UL;

  return capture;
}

// map entry 7449 (= 25 -> 29); note that
// `s1` must be the active player
static inline bool _do_move_25_29(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 29 + 32 * (blacks_turn || GET_64(s1, 57)));

  // clear `from` bit
  s1 &= 18302628885600141311UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 7705 (= 25 -> 30); note that
// `s1` must be the active player
static inline bool _do_move_25_30(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 30 + 32 * (blacks_turn || GET_64(s1, 57)));

  // clear `from` bit
  s1 &= 18302628885600141311UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5914 (= 26 -> 23); note that
// `s1` must be the active player
static inline bool _do_move_26_23(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 23 + 32 * GET_64(s1, 58));

  // clear `from` bit
  s1 &= 18158513697490731007UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4890 (= 26 -> 19); note that
// `s1` must be the active player
static inline bool _do_move_26_19(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 19 + 32 * GET_64(s1, 58));

  // clear `from` bit
  s1 &= 18158513697490731007UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 36028797027352576UL) == 0);
  const bool capture = s2 & 36028797027352576UL;
  s2 &= 18410715276682199039UL;

  return capture;
}

// map entry 5658 (= 26 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_26_22(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 58));

  // clear `from` bit
  s1 &= 18158513697490731007UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4378 (= 26 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_26_17(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 58));

  // clear `from` bit
  s1 &= 18158513697490731007UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 18014398513676288UL) == 0);
  const bool capture = s2 & 18014398513676288UL;
  s2 &= 18428729675195875327UL;

  return capture;
}

// map entry 3354 (= 26 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_26_13(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 58));

  // clear `from` bit
  s1 &= 18158513697490731007UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 18577348467228672UL) == 0);
  const bool capture = s2 & 18577348467228672UL;
  s2 &= 18428166725242322943UL;

  return capture;
}

// map entry 2074 (= 26 -> 8); note that
// `s1` must be the active player
static inline bool _do_move_26_8(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 8 + 32 * GET_64(s1, 58));

  // clear `from` bit
  s1 &= 18158513697490731007UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 18612532839325696UL) == 0);
  const bool capture = s2 & 18612532839325696UL;
  s2 &= 18428131540870225919UL;

  return capture;
}

// map entry 1050 (= 26 -> 4); note that
// `s1` must be the active player
static inline bool _do_move_26_4(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 4 + 32 * GET_64(s1, 58));

  // clear `from` bit
  s1 &= 18158513697490731007UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 18613632350953728UL) == 0);
  const bool capture = s2 & 18613632350953728UL;
  s2 &= 18428130441358597887UL;

  return capture;
}

// map entry 7706 (= 26 -> 30); note that
// `s1` must be the active player
static inline bool _do_move_26_30(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 30 + 32 * (blacks_turn || GET_64(s1, 58)));

  // clear `from` bit
  s1 &= 18158513697490731007UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 7962 (= 26 -> 31); note that
// `s1` must be the active player
static inline bool _do_move_26_31(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 31 + 32 * (blacks_turn || GET_64(s1, 58)));

  // clear `from` bit
  s1 &= 18158513697490731007UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5915 (= 27 -> 23); note that
// `s1` must be the active player
static inline bool _do_move_27_23(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 23 + 32 * GET_64(s1, 59));

  // clear `from` bit
  s1 &= 17870283321271910399UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 4635 (= 27 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_27_18(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 59));

  // clear `from` bit
  s1 &= 17870283321271910399UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 36028797027352576UL) == 0);
  const bool capture = s2 & 36028797027352576UL;
  s2 &= 18410715276682199039UL;

  return capture;
}

// map entry 3611 (= 27 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_27_14(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 59));

  // clear `from` bit
  s1 &= 17870283321271910399UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37154696934457344UL) == 0);
  const bool capture = s2 & 37154696934457344UL;
  s2 &= 18409589376775094271UL;

  return capture;
}

// map entry 2331 (= 27 -> 9); note that
// `s1` must be the active player
static inline bool _do_move_27_9(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 9 + 32 * GET_64(s1, 59));

  // clear `from` bit
  s1 &= 17870283321271910399UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37225065678651392UL) == 0);
  const bool capture = s2 & 37225065678651392UL;
  s2 &= 18409519008030900223UL;

  return capture;
}

// map entry 1307 (= 27 -> 5); note that
// `s1` must be the active player
static inline bool _do_move_27_5(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 5 + 32 * GET_64(s1, 59));

  // clear `from` bit
  s1 &= 17870283321271910399UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37227264701907456UL) == 0);
  const bool capture = s2 & 37227264701907456UL;
  s2 &= 18409516809007644159UL;

  return capture;
}

// map entry 27 (= 27 -> 0); note that
// `s1` must be the active player
static inline bool _do_move_27_0(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 0 + 32 * (!blacks_turn || GET_64(s1, 59)));

  // clear `from` bit
  s1 &= 17870283321271910399UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 37227402140860960UL) == 0);
  const bool capture = s2 & 37227402140860960UL;
  s2 &= 18409516671568690655UL;

  return capture;
}

// map entry 7963 (= 27 -> 31); note that
// `s1` must be the active player
static inline bool _do_move_27_31(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 31 + 32 * (blacks_turn || GET_64(s1, 59)));

  // clear `from` bit
  s1 &= 17870283321271910399UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 6172 (= 28 -> 24); note that
// `s1` must be the active player
static inline bool _do_move_28_24(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 24 + 32 * GET_64(s1, 60));

  // clear `from` bit
  s1 &= 17293822568834269183UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5404 (= 28 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_28_21(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 60));

  // clear `from` bit
  s1 &= 17293822568834269183UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 72057594054705152UL) == 0);
  const bool capture = s2 & 72057594054705152UL;
  s2 &= 18374686479654846463UL;

  return capture;
}

// map entry 4380 (= 28 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_28_17(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 60));

  // clear `from` bit
  s1 &= 17293822568834269183UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 81064793311543296UL) == 0);
  const bool capture = s2 & 81064793311543296UL;
  s2 &= 18365679280398008319UL;

  return capture;
}

// map entry 3612 (= 28 -> 14); note that
// `s1` must be the active player
static inline bool _do_move_28_14(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 14 + 32 * GET_64(s1, 60));

  // clear `from` bit
  s1 &= 17293822568834269183UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 81627743265095680UL) == 0);
  const bool capture = s2 & 81627743265095680UL;
  s2 &= 18365116330444455935UL;

  return capture;
}

// map entry 2588 (= 28 -> 10); note that
// `s1` must be the active player
static inline bool _do_move_28_10(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 10 + 32 * GET_64(s1, 60));

  // clear `from` bit
  s1 &= 17293822568834269183UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 81698112009289728UL) == 0);
  const bool capture = s2 & 81698112009289728UL;
  s2 &= 18365045961700261887UL;

  return capture;
}

// map entry 1820 (= 28 -> 7); note that
// `s1` must be the active player
static inline bool _do_move_28_7(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 7 + 32 * GET_64(s1, 60));

  // clear `from` bit
  s1 &= 17293822568834269183UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 81702510055801856UL) == 0);
  const bool capture = s2 & 81702510055801856UL;
  s2 &= 18365041563653749759UL;

  return capture;
}

// map entry 796 (= 28 -> 3); note that
// `s1` must be the active player
static inline bool _do_move_28_3(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 3 + 32 * (!blacks_turn || GET_64(s1, 60)));

  // clear `from` bit
  s1 &= 17293822568834269183UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 81703059811615872UL) == 0);
  const bool capture = s2 & 81703059811615872UL;
  s2 &= 18365041013897935743UL;

  return capture;
}

// map entry 6429 (= 29 -> 25); note that
// `s1` must be the active player
static inline bool _do_move_29_25(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 25 + 32 * GET_64(s1, 61));

  // clear `from` bit
  s1 &= 16140901063958986751UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5661 (= 29 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_29_22(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 61));

  // clear `from` bit
  s1 &= 16140901063958986751UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 144115188109410304UL) == 0);
  const bool capture = s2 & 144115188109410304UL;
  s2 &= 18302628885600141311UL;

  return capture;
}

// map entry 4637 (= 29 -> 18); note that
// `s1` must be the active player
static inline bool _do_move_29_18(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 18 + 32 * GET_64(s1, 61));

  // clear `from` bit
  s1 &= 16140901063958986751UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 162129586623086592UL) == 0);
  const bool capture = s2 & 162129586623086592UL;
  s2 &= 18284614487086465023UL;

  return capture;
}

// map entry 3869 (= 29 -> 15); note that
// `s1` must be the active player
static inline bool _do_move_29_15(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 15 + 32 * GET_64(s1, 61));

  // clear `from` bit
  s1 &= 16140901063958986751UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 163255486530191360UL) == 0);
  const bool capture = s2 & 163255486530191360UL;
  s2 &= 18283488587179360255UL;

  return capture;
}

// map entry 2845 (= 29 -> 11); note that
// `s1` must be the active player
static inline bool _do_move_29_11(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 11 + 32 * GET_64(s1, 61));

  // clear `from` bit
  s1 &= 16140901063958986751UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 163396224018579456UL) == 0);
  const bool capture = s2 & 163396224018579456UL;
  s2 &= 18283347849690972159UL;

  return capture;
}

// map entry 6173 (= 29 -> 24); note that
// `s1` must be the active player
static inline bool _do_move_29_24(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 24 + 32 * GET_64(s1, 61));

  // clear `from` bit
  s1 &= 16140901063958986751UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5149 (= 29 -> 20); note that
// `s1` must be the active player
static inline bool _do_move_29_20(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 20 + 32 * GET_64(s1, 61));

  // clear `from` bit
  s1 &= 16140901063958986751UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 72057594054705152UL) == 0);
  const bool capture = s2 & 72057594054705152UL;
  s2 &= 18374686479654846463UL;

  return capture;
}

// map entry 6686 (= 30 -> 26); note that
// `s1` must be the active player
static inline bool _do_move_30_26(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 26 + 32 * GET_64(s1, 62));

  // clear `from` bit
  s1 &= 13835058054208421887UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5918 (= 30 -> 23); note that
// `s1` must be the active player
static inline bool _do_move_30_23(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 23 + 32 * GET_64(s1, 62));

  // clear `from` bit
  s1 &= 13835058054208421887UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 288230376218820608UL) == 0);
  const bool capture = s2 & 288230376218820608UL;
  s2 &= 18158513697490731007UL;

  return capture;
}

// map entry 4894 (= 30 -> 19); note that
// `s1` must be the active player
static inline bool _do_move_30_19(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 19 + 32 * GET_64(s1, 62));

  // clear `from` bit
  s1 &= 13835058054208421887UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 324259173246173184UL) == 0);
  const bool capture = s2 & 324259173246173184UL;
  s2 &= 18122484900463378431UL;

  return capture;
}

// map entry 6430 (= 30 -> 25); note that
// `s1` must be the active player
static inline bool _do_move_30_25(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 25 + 32 * GET_64(s1, 62));

  // clear `from` bit
  s1 &= 13835058054208421887UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5406 (= 30 -> 21); note that
// `s1` must be the active player
static inline bool _do_move_30_21(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 21 + 32 * GET_64(s1, 62));

  // clear `from` bit
  s1 &= 13835058054208421887UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 144115188109410304UL) == 0);
  const bool capture = s2 & 144115188109410304UL;
  s2 &= 18302628885600141311UL;

  return capture;
}

// map entry 4126 (= 30 -> 16); note that
// `s1` must be the active player
static inline bool _do_move_30_16(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 16 + 32 * GET_64(s1, 62));

  // clear `from` bit
  s1 &= 13835058054208421887UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 153122387366248448UL) == 0);
  const bool capture = s2 & 153122387366248448UL;
  s2 &= 18293621686343303167UL;

  return capture;
}

// map entry 3102 (= 30 -> 12); note that
// `s1` must be the active player
static inline bool _do_move_30_12(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 12 + 32 * GET_64(s1, 62));

  // clear `from` bit
  s1 &= 13835058054208421887UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 153403862343024640UL) == 0);
  const bool capture = s2 & 153403862343024640UL;
  s2 &= 18293340211366526975UL;

  return capture;
}

// map entry 6943 (= 31 -> 27); note that
// `s1` must be the active player
static inline bool _do_move_31_27(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 27 + 32 * GET_64(s1, 63));

  // clear `from` bit
  s1 &= 9223372034707292159UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 6687 (= 31 -> 26); note that
// `s1` must be the active player
static inline bool _do_move_31_26(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 26 + 32 * GET_64(s1, 63));

  // clear `from` bit
  s1 &= 9223372034707292159UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 0UL) == 0);
  const bool capture = s2 & 0UL;
  s2 &= 18446744073709551615UL;

  return capture;
}

// map entry 5663 (= 31 -> 22); note that
// `s1` must be the active player
static inline bool _do_move_31_22(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 22 + 32 * GET_64(s1, 63));

  // clear `from` bit
  s1 &= 9223372034707292159UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 288230376218820608UL) == 0);
  const bool capture = s2 & 288230376218820608UL;
  s2 &= 18158513697490731007UL;

  return capture;
}

// map entry 4383 (= 31 -> 17); note that
// `s1` must be the active player
static inline bool _do_move_31_17(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 17 + 32 * GET_64(s1, 63));

  // clear `from` bit
  s1 &= 9223372034707292159UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 306244774732496896UL) == 0);
  const bool capture = s2 & 306244774732496896UL;
  s2 &= 18140499298977054719UL;

  return capture;
}

// map entry 3359 (= 31 -> 13); note that
// `s1` must be the active player
static inline bool _do_move_31_13(Slice &s1, Slice &s2,
                                  const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 13 + 32 * GET_64(s1, 63));

  // clear `from` bit
  s1 &= 9223372034707292159UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 306807724686049280UL) == 0);
  const bool capture = s2 & 306807724686049280UL;
  s2 &= 18139936349023502335UL;

  return capture;
}

// map entry 2079 (= 31 -> 8); note that
// `s1` must be the active player
static inline bool _do_move_31_8(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 8 + 32 * GET_64(s1, 63));

  // clear `from` bit
  s1 &= 9223372034707292159UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 306842909058146304UL) == 0);
  const bool capture = s2 & 306842909058146304UL;
  s2 &= 18139901164651405311UL;

  return capture;
}

// map entry 1055 (= 31 -> 4); note that
// `s1` must be the active player
static inline bool _do_move_31_4(Slice &s1, Slice &s2, const bool blacks_turn) {
  // set the `to` bit
  SET_64(s1, 4 + 32 * GET_64(s1, 63));

  // clear `from` bit
  s1 &= 9223372034707292159UL;

  // clear any token in between (zero or one for a valid move)
  assert((s1 & 306844008569774336UL) == 0);
  const bool capture = s2 & 306844008569774336UL;
  s2 &= 18139900065139777279UL;

  return capture;
}

using MoveFun =
    std::function<bool(Slice &s1, Slice &s2, const bool blacks_turn)>;
static const std::unordered_map<Move, MoveFun> move_fun = {
    {1024, _do_move_0_4},   {1280, _do_move_0_5},   {2304, _do_move_0_9},
    {3584, _do_move_0_14},  {4608, _do_move_0_18},  {5888, _do_move_0_23},
    {6912, _do_move_0_27},  {1281, _do_move_1_5},   {2049, _do_move_1_8},
    {3073, _do_move_1_12},  {1537, _do_move_1_6},   {2561, _do_move_1_10},
    {3841, _do_move_1_15},  {4865, _do_move_1_19},  {1538, _do_move_2_6},
    {2306, _do_move_2_9},   {3330, _do_move_2_13},  {4098, _do_move_2_16},
    {5122, _do_move_2_20},  {1794, _do_move_2_7},   {2818, _do_move_2_11},
    {1795, _do_move_3_7},   {2563, _do_move_3_10},  {3587, _do_move_3_14},
    {4355, _do_move_3_17},  {5379, _do_move_3_21},  {6147, _do_move_3_24},
    {7171, _do_move_3_28},  {4, _do_move_4_0},      {2052, _do_move_4_8},
    {3332, _do_move_4_13},  {4356, _do_move_4_17},  {5636, _do_move_4_22},
    {6660, _do_move_4_26},  {7940, _do_move_4_31},  {261, _do_move_5_1},
    {5, _do_move_5_0},      {2053, _do_move_5_8},   {3077, _do_move_5_12},
    {2309, _do_move_5_9},   {3589, _do_move_5_14},  {4613, _do_move_5_18},
    {5893, _do_move_5_23},  {6917, _do_move_5_27},  {518, _do_move_6_2},
    {262, _do_move_6_1},    {2310, _do_move_6_9},   {3334, _do_move_6_13},
    {4102, _do_move_6_16},  {5126, _do_move_6_20},  {2566, _do_move_6_10},
    {3846, _do_move_6_15},  {4870, _do_move_6_19},  {775, _do_move_7_3},
    {519, _do_move_7_2},    {2567, _do_move_7_10},  {3591, _do_move_7_14},
    {4359, _do_move_7_17},  {5383, _do_move_7_21},  {6151, _do_move_7_24},
    {7175, _do_move_7_28},  {2823, _do_move_7_11},  {1288, _do_move_8_5},
    {264, _do_move_8_1},    {1032, _do_move_8_4},   {3080, _do_move_8_12},
    {3336, _do_move_8_13},  {4360, _do_move_8_17},  {5640, _do_move_8_22},
    {6664, _do_move_8_26},  {7944, _do_move_8_31},  {1545, _do_move_9_6},
    {521, _do_move_9_2},    {1289, _do_move_9_5},   {9, _do_move_9_0},
    {3337, _do_move_9_13},  {4105, _do_move_9_16},  {5129, _do_move_9_20},
    {3593, _do_move_9_14},  {4617, _do_move_9_18},  {5897, _do_move_9_23},
    {6921, _do_move_9_27},  {1802, _do_move_10_7},  {778, _do_move_10_3},
    {1546, _do_move_10_6},  {266, _do_move_10_1},   {3594, _do_move_10_14},
    {4362, _do_move_10_17}, {5386, _do_move_10_21}, {6154, _do_move_10_24},
    {7178, _do_move_10_28}, {3850, _do_move_10_15}, {4874, _do_move_10_19},
    {1803, _do_move_11_7},  {523, _do_move_11_2},   {3851, _do_move_11_15},
    {4619, _do_move_11_18}, {5643, _do_move_11_22}, {6411, _do_move_11_25},
    {7435, _do_move_11_29}, {2060, _do_move_12_8},  {1292, _do_move_12_5},
    {268, _do_move_12_1},   {4108, _do_move_12_16}, {5388, _do_move_12_21},
    {6412, _do_move_12_25}, {7692, _do_move_12_30}, {2317, _do_move_13_9},
    {1549, _do_move_13_6},  {525, _do_move_13_2},   {2061, _do_move_13_8},
    {1037, _do_move_13_4},  {4109, _do_move_13_16}, {5133, _do_move_13_20},
    {4365, _do_move_13_17}, {5645, _do_move_13_22}, {6669, _do_move_13_26},
    {7949, _do_move_13_31}, {2574, _do_move_14_10}, {1806, _do_move_14_7},
    {782, _do_move_14_3},   {2318, _do_move_14_9},  {1294, _do_move_14_5},
    {14, _do_move_14_0},    {4366, _do_move_14_17}, {5390, _do_move_14_21},
    {6158, _do_move_14_24}, {7182, _do_move_14_28}, {4622, _do_move_14_18},
    {5902, _do_move_14_23}, {6926, _do_move_14_27}, {2831, _do_move_15_11},
    {2575, _do_move_15_10}, {1551, _do_move_15_6},  {271, _do_move_15_1},
    {4623, _do_move_15_18}, {5647, _do_move_15_22}, {6415, _do_move_15_25},
    {7439, _do_move_15_29}, {4879, _do_move_15_19}, {3344, _do_move_16_13},
    {2320, _do_move_16_9},  {1552, _do_move_16_6},  {528, _do_move_16_2},
    {3088, _do_move_16_12}, {5136, _do_move_16_20}, {5392, _do_move_16_21},
    {6416, _do_move_16_25}, {7696, _do_move_16_30}, {3601, _do_move_17_14},
    {2577, _do_move_17_10}, {1809, _do_move_17_7},  {785, _do_move_17_3},
    {3345, _do_move_17_13}, {2065, _do_move_17_8},  {1041, _do_move_17_4},
    {5393, _do_move_17_21}, {6161, _do_move_17_24}, {7185, _do_move_17_28},
    {5649, _do_move_17_22}, {6673, _do_move_17_26}, {7953, _do_move_17_31},
    {3858, _do_move_18_15}, {2834, _do_move_18_11}, {3602, _do_move_18_14},
    {2322, _do_move_18_9},  {1298, _do_move_18_5},  {18, _do_move_18_0},
    {5650, _do_move_18_22}, {6418, _do_move_18_25}, {7442, _do_move_18_29},
    {5906, _do_move_18_23}, {6930, _do_move_18_27}, {3859, _do_move_19_15},
    {2579, _do_move_19_10}, {1555, _do_move_19_6},  {275, _do_move_19_1},
    {5907, _do_move_19_23}, {6675, _do_move_19_26}, {7699, _do_move_19_30},
    {4116, _do_move_20_16}, {3348, _do_move_20_13}, {2324, _do_move_20_9},
    {1556, _do_move_20_6},  {532, _do_move_20_2},   {6164, _do_move_20_24},
    {7444, _do_move_20_29}, {4373, _do_move_21_17}, {3605, _do_move_21_14},
    {2581, _do_move_21_10}, {1813, _do_move_21_7},  {789, _do_move_21_3},
    {4117, _do_move_21_16}, {3093, _do_move_21_12}, {6165, _do_move_21_24},
    {7189, _do_move_21_28}, {6421, _do_move_21_25}, {7701, _do_move_21_30},
    {4630, _do_move_22_18}, {3862, _do_move_22_15}, {2838, _do_move_22_11},
    {4374, _do_move_22_17}, {3350, _do_move_22_13}, {2070, _do_move_22_8},
    {1046, _do_move_22_4},  {6422, _do_move_22_25}, {7446, _do_move_22_29},
    {6678, _do_move_22_26}, {7958, _do_move_22_31}, {4887, _do_move_23_19},
    {4631, _do_move_23_18}, {3607, _do_move_23_14}, {2327, _do_move_23_9},
    {1303, _do_move_23_5},  {23, _do_move_23_0},    {6679, _do_move_23_26},
    {7703, _do_move_23_30}, {6935, _do_move_23_27}, {5400, _do_move_24_21},
    {4376, _do_move_24_17}, {3608, _do_move_24_14}, {2584, _do_move_24_10},
    {1816, _do_move_24_7},  {792, _do_move_24_3},   {5144, _do_move_24_20},
    {7192, _do_move_24_28}, {7448, _do_move_24_29}, {5657, _do_move_25_22},
    {4633, _do_move_25_18}, {3865, _do_move_25_15}, {2841, _do_move_25_11},
    {5401, _do_move_25_21}, {4121, _do_move_25_16}, {3097, _do_move_25_12},
    {7449, _do_move_25_29}, {7705, _do_move_25_30}, {5914, _do_move_26_23},
    {4890, _do_move_26_19}, {5658, _do_move_26_22}, {4378, _do_move_26_17},
    {3354, _do_move_26_13}, {2074, _do_move_26_8},  {1050, _do_move_26_4},
    {7706, _do_move_26_30}, {7962, _do_move_26_31}, {5915, _do_move_27_23},
    {4635, _do_move_27_18}, {3611, _do_move_27_14}, {2331, _do_move_27_9},
    {1307, _do_move_27_5},  {27, _do_move_27_0},    {7963, _do_move_27_31},
    {6172, _do_move_28_24}, {5404, _do_move_28_21}, {4380, _do_move_28_17},
    {3612, _do_move_28_14}, {2588, _do_move_28_10}, {1820, _do_move_28_7},
    {796, _do_move_28_3},   {6429, _do_move_29_25}, {5661, _do_move_29_22},
    {4637, _do_move_29_18}, {3869, _do_move_29_15}, {2845, _do_move_29_11},
    {6173, _do_move_29_24}, {5149, _do_move_29_20}, {6686, _do_move_30_26},
    {5918, _do_move_30_23}, {4894, _do_move_30_19}, {6430, _do_move_30_25},
    {5406, _do_move_30_21}, {4126, _do_move_30_16}, {3102, _do_move_30_12},
    {6943, _do_move_31_27}, {6687, _do_move_31_26}, {5663, _do_move_31_22},
    {4383, _do_move_31_17}, {3359, _do_move_31_13}, {2079, _do_move_31_8},
    {1055, _do_move_31_4},
};

bool do_move_bk(Slice &bk, Slice &wt, const Move &move) {
  // consistency check: this func shall be called only if there's a black token
  // where the move is to start from
  if (!GET_64(bk, get_from(move)) && !GET_64(bk, get_from(move) + 32))
    throw std::runtime_error(
        "No white token where move should start: bk=" + to_string(bk) +
        ", wt=" + to_string(wt) + ", from=" + to_string(get_from(move)) +
        " (to=" + to_string(get_to(move)) + ")");

  // ensure that we have a look up function for the `move`
  if (move_fun.find(clean_move(move)) == move_fun.end())
    throw std::runtime_error("Invalid move: from=" + to_string(get_from(move)) +
                             ", to=" + to_string(get_to(move)));

  // Note: first argument shall be the active player
  return move_fun.at(clean_move(move))(bk, wt, true);
}

bool do_move_wt(Slice &bk, Slice &wt, const Move &move) {
  // consistency check: this func shall be called only if there's a white token
  // where the move is to start from
  if (!GET_64(wt, get_from(move)) && !GET_64(wt, get_from(move) + 32)) {
    print_board(bk, wt, std::vector<Move>(), &move);
    throw std::runtime_error("No white token where move should start: bk=" +
                             std::to_string(bk) + ", wt=" + std::to_string(wt) +
                             ", from=" + std::to_string(get_from(move)) +
                             " (to=" + std::to_string(get_to(move)) + ")");
  }

  // ensure that we have a look up function for the `move`
  if (move_fun.find(clean_move(move)) == move_fun.end())
    throw std::runtime_error("Invalid move: from=" + to_string(get_from(move)) +
                             ", to=" + to_string(get_to(move)));

  // Note: first argument shall be the active player
  return move_fun.at(clean_move(move))(wt, bk, false);
}

} // namespace shashki