#include "tests.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include "_board_internal.h"
#include "game_history.h"
#include "shared.h"
#include "strategies.h"

using namespace std;

namespace shashki {

static random_device r;
static seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
static shared_ptr<mt19937> eng = make_shared<mt19937>(seed);
static uniform_int_distribution<> uniform_01(0, 1);

bool same_move_options(const std::vector<Move>& xs, const std::vector<Move>& ys,
                       bool verbose) {
  std::vector<Move> xs_sorted(xs), ys_sorted(ys);
  std::sort(xs_sorted.begin(), xs_sorted.end());
  std::sort(ys_sorted.begin(), ys_sorted.end());

  bool ok = xs.size() == ys.size();
  for (int i = 0; ok && i < (int)xs_sorted.size(); ++i)
    if (get_from(xs_sorted[i]) != get_from(ys_sorted[i]) ||
        get_to(xs_sorted[i]) != get_to(ys_sorted[i]))
      ok = false;

  if (!ok && verbose) {
    printf("Mismatch in same_move_options()\n> left:  ");
    for (const auto& x : xs) printf("%s, ", to_string(x).c_str());
    printf("\n> right: ");
    for (const auto& y : ys) printf("%s, ", to_string(y).c_str());
    printf("\n>");
  }

  return ok;
}

void test_valid_moves() {
  const size_t N = 50000UL;
  Slice bk, wt;
  bool blacks_turn = true;

  for (size_t i = 0; i < N; ++i) {
    random_board(bk, wt);
    blacks_turn = !blacks_turn;

    auto moves_main = valid_moves(bk, wt, blacks_turn);
    auto moves_alt = valid_moves_alternate_impl(bk, wt, blacks_turn);

    if (!same_move_options(moves_main, moves_alt, true)) {
      printf("======== ERROR: MISMATCH at iter %lu ========\n", i);
      printf("Player: %s\n", blacks_turn ? "black" : "white");
      printf("main impl: ");
      print_board(bk, wt, moves_main);
      printf("\nalternate impl: ");
      print_board(bk, wt, moves_alt);
      printf("==================================\n");
      // debug info
      if (blacks_turn) {
        const Slice top = bk, bottom = wt;

        const Slice top_any = (top >> 32) | top;
        const Slice bottom_any = (bottom >> 32) | bottom;
        const Slice empty = ~(top_any | bottom_any) & 0xffffffff;
        const Slice bace = (bottom_any << 32) | empty;

        printf("moves1: ");
        for (const auto& x : moves_main) printf("%s, ", to_string(x).c_str());
        printf("\nmoves2: ");
        for (const auto& x : moves_alt) printf("%s, ", to_string(x).c_str());
        printf("\n");

        printf("    bottom=%lu\n", bottom);
        printf("    top_any=%lu\n", top_any);
        printf("    bottom_any=%lu\n", bottom_any);
        printf("    empty=%lu\n", empty);
        printf("    top=%lu\n", top);
        printf("    bace=%lu\n", bace);
      }

      assert(same_move_options(moves_main, moves_alt, true));  // "throw"
    }

    if ((i + 1) % 1000000 == 0)
      printf("test_valid_moves(): %luM out of %luM done\n", (i + 1) / 1000000,
             N / 1000000);
  }
}

void test_valid_capturing_moves_from() {
  const size_t N = 50000UL;
  Slice bk, wt;
  bool blacks_turn = true;

  for (size_t i = 0; i < N; ++i) {
    random_board(bk, wt);
    blacks_turn = !blacks_turn;

    // test we get the same valid moves starting from every possible location
    for (Loc j = 0; j < 32; ++j) {
      if (blacks_turn && !(GET_64(bk, j) || GET_64(bk, j + 32)) ||
          !blacks_turn && !(GET_64(wt, j) || GET_64(wt, j + 32)))
        continue;

      auto moves_main = valid_capturing_moves_from(bk, wt, j);
      auto moves_alt =
          valid_capturing_moves_from_alternate_impl(bk, wt, blacks_turn, j);

      if (!same_move_options(moves_main, moves_alt, true)) {
        printf("======== ERROR: MISMATCH at iter %lu ========\n", i);
        printf("Player: %s\n", blacks_turn ? "black" : "white");
        printf("Start index: %lu\n", j);
        printf("main impl: ");
        print_board(bk, wt, moves_main);
        printf("\nalternate impl: ");
        print_board(bk, wt, moves_alt);
        printf("==================================\n");
        // debug info
        if (blacks_turn) {
          const Slice top = bk, bottom = wt;

          const Slice top_any = (top >> 32) | top;
          const Slice bottom_any = (bottom >> 32) | bottom;
          const Slice empty = ~(top_any | bottom_any) & 0xffffffff;
          const Slice bace = (bottom_any << 32) | empty;

          printf("moves1: ");
          for (const auto& x : moves_main) printf("%s, ", to_string(x).c_str());
          printf("\nmoves2: ");
          for (const auto& x : moves_alt) printf("%s, ", to_string(x).c_str());
          printf("\n");

          printf("    bottom=%lu\n", bottom);
          printf("    top_any=%lu\n", top_any);
          printf("    bottom_any=%lu\n", bottom_any);
          printf("    empty=%lu\n", empty);
          printf("    top=%lu\n", top);
          printf("    bace=%lu\n", bace);
        }

        assert(same_move_options(moves_main, moves_alt, true));  // "throw"
      }
    }

    if ((i + 1) % 1000000 == 0)
      printf("test_valid_moves(): %luM out of %luM done\n", (i + 1) / 1000000,
             N / 1000000);
  }
}

void test_do_move() {
  const size_t N = 50000UL;
  Slice bk, wt;
  bool blacks_turn = true;

  for (size_t i = 0; i < N; ++i) {
    vector<Move> moves;
    while (moves.empty()) {
      random_board(bk, wt);
      blacks_turn = uniform_01(*eng);
      moves = valid_moves(bk, wt, blacks_turn);
    }

    for (const Move& mv : moves) {
      Slice s1(bk), s2(wt);
      Slice s1_alt(bk), s2_alt(wt);
      bool capt, capt_alt;

      if (blacks_turn) {
        capt = do_move_bk(s1, s2, mv);
        capt_alt = do_move_alternate_impl(s1_alt, s2_alt, mv, blacks_turn);
      } else {
        capt = do_move_wt(s1, s2, mv);
        capt_alt = do_move_alternate_impl(s2_alt, s1_alt, mv, blacks_turn);
      }

      if (s1 != s1_alt || s2 != s2_alt || capt != capt_alt) {
        printf("======== ERROR: MISMATCH at iter %lu ========\n", i);
        printf("Player: %s\n", blacks_turn ? "black" : "white");
        printf("Selected move: %lu -> %lu\n", get_from(mv), get_to(mv));
        printf("Options:    ");
        print_board(bk, wt, moves, &mv);
        printf("\nCur impl:  capture=%d  ", capt);
        print_board(s1, s2);
        printf("\nAlt impl:  capture=%d  ", capt_alt);
        print_board(s1_alt, s2_alt);
        printf("==================================\n");

        throw runtime_error("Fix this");
      }
    }
  }
}

void test_rotate_slice() {
  Slice s = (1UL << 28) | (1UL << 27) | (1UL << 31) | (1UL << 62) |
            (1UL << 61) | (1UL << 60) | (1UL << 37) | (1UL << 32);
  Slice f = rotate_slice(s);
  Slice ss = rotate_slice(f);

  assert(f == 9511602473136029721UL);
  assert(s == ss);
}

void test_get_set() {
  Slice s = 0UL;
  for (int i = 0; i < 64; ++i) {
    assert(GET_64(s, i) == 0);
    SET_64(s, i);
    assert(GET_64(s, i) == 1);
  }
}

void test_make_move() {
  Move m = make_move(28, 3);
  assert(get_from(m) == 28);
  assert(get_to(m) == 3);

  m = make_move(3, 28);
  assert(get_from(m) == 3);
  assert(get_to(m) == 28);

  m = make_move(5, 0);
  assert(get_from(m) == 5);
  assert(get_to(m) == 0);
}

void test_one_more() {
  const std::vector<int> truth_ne{0, 1, 2, 3, 11, 19, 27};
  const std::vector<int> truth_nw{0, 1, 2, 3, 4, 12, 20, 28};
  const std::vector<int> truth_sw{4, 12, 20, 28, 29, 30, 31};
  const std::vector<int> truth_se{3, 11, 19, 27, 28, 29, 30, 31};

  for (int i = 0; i < 32; ++i) {
    assert(one_more_ne(i) ==
           (std::find(truth_ne.begin(), truth_ne.end(), i) == truth_ne.end()));
    assert(one_more_nw(i) ==
           (std::find(truth_nw.begin(), truth_nw.end(), i) == truth_nw.end()));
    assert(one_more_sw(i) ==
           (std::find(truth_sw.begin(), truth_sw.end(), i) == truth_sw.end()));
    assert(one_more_se(i) ==
           (std::find(truth_se.begin(), truth_se.end(), i) == truth_se.end()));
  }
}

void test__can_king_capture_along_beam_ne() {
  // test data
  const Loc king_loc = 17;
  const std::vector<std::vector<int>> bottom_loc = {
      {14}, {13}, {21}, {12}, {10},   {8},     {24},    {26},    {7},
      {4},  {28}, {31}, {3},  {3, 7}, {3, 10}, {3, 14}, {7, 10}, {10, 14}};
  const std::vector<bool> answers = {true,  false, false, false, true,  false,
                                     false, false, true,  false, false, false,
                                     false, false, true,  true,  false, false};

  assert(bottom_loc.size() == answers.size());
  for (int i = 0; i < (int)bottom_loc.size(); ++i) {
    // create board as configured
    Slice top = 0UL, bottom = 0UL;
    for (auto l : bottom_loc[i]) SET_64(bottom, l);

    const Slice top_any = (top >> 32) | top;
    const Slice bottom_any = (bottom >> 32) | bottom;
    const Slice is_empty = ~(top_any | bottom_any);

    const bool res = _can_king_capture_along_beam(
        king_loc, ne_offsets, one_more_ne, is_empty, bottom_any);

    assert(res == answers[i]);
  }
}

void test__can_king_capture_from() {
  Slice top = 0UL, bottom = 0UL;
  SET_64(bottom, 14);
  SET_64(bottom, 10);
  SET_64(bottom, 26);

  const Slice top_any = (top >> 32) | top;
  const Slice bottom_any = (bottom >> 32) | bottom;
  const Slice is_empty = ~(top_any | bottom_any);

  const Loc loc = 17;
  const bool ans = _can_king_capture_from<ne_offsets>(loc, one_more_ne,
                                                      is_empty, bottom_any);
  assert(ans);
}

void test_men_simple() {
  std::vector<Move> vm, truth;
  Slice bk, wt;

  // black, single token
  bk = wt = 0UL;
  SET_64(bk, 0);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(0, 4), make_move(0, 5)};
  assert(same_move_options(vm, truth, true));

  // white, single token
  bk = wt = 0UL;
  SET_64(wt, 3);
  vm = valid_moves(bk, wt, false);
  assert(vm.empty());

  // white, single token
  bk = wt = 0UL;
  SET_64(wt, 5);
  vm = valid_moves(bk, wt, false);
  truth = std::vector<Move>{make_move(5, 0), make_move(5, 1)};
  assert(same_move_options(vm, truth, true));
}

void test_men_multiple() {
  std::vector<Move> vm, truth;
  Slice bk, wt;

  // black, mulitple tokens
  bk = wt = 0UL;
  SET_64(bk, 0);
  SET_64(bk, 1);
  SET_64(bk, 12);
  SET_64(bk, 19);
  SET_64(bk, 28);
  SET_64(bk, 29);
  SET_64(bk, 31);
  vm = valid_moves(bk, wt, true);
  truth =
      std::vector<Move>{make_move(0, 4),   make_move(0, 5), make_move(12, 16),
                        make_move(19, 23), make_move(1, 5), make_move(1, 6)};
  assert(same_move_options(vm, truth, true));
}

void test_men_capture() {
  std::vector<Move> vm, truth;
  Slice bk, wt;

  // black capturing white, forward
  bk = wt = 0UL;
  SET_64(bk, 0);
  SET_64(wt, 5);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(0, 9)};
  assert(same_move_options(vm, truth, true));

  // black capturing white, backward
  bk = wt = 0UL;
  SET_64(bk, 9);
  SET_64(wt, 5);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(9, 0)};
  assert(same_move_options(vm, truth, true));

  // black capturing white, 1 option due to blocking at edges
  bk = wt = 0UL;
  SET_64(bk, 7);
  SET_64(wt, 2);
  SET_64(wt, 3);
  SET_64(wt, 10);
  SET_64(wt, 11);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(7, 14)};
  assert(same_move_options(vm, truth, true));

  // black capturing white, four possibilities
  bk = wt = 0UL;
  SET_64(bk, 17);
  SET_64(wt, 13);
  SET_64(wt, 14);
  SET_64(wt, 21);
  SET_64(wt, 22);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(17, 8), make_move(17, 10),
                            make_move(17, 24), make_move(17, 26)};
  assert(same_move_options(vm, truth, true));

  // black no capture due to blocking, three regular moves possible
  bk = wt = 0UL;
  SET_64(bk, 17);
  SET_64(wt, 13);
  SET_64(wt, 14);
  SET_64(wt, 21);
  SET_64(wt, 22);
  SET_64(wt, 8);
  SET_64(bk, 10);
  SET_64(wt, 24);
  SET_64(bk, 26);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(10, 15), make_move(26, 30),
                            make_move(26, 31)};
  assert(same_move_options(vm, truth, true));

  // (cnt'd) black no captures CLEAR_64(bk, 17); vm = valid_moves(bk, wt,
  // true); truth =
  std::vector<Move>{make_move(10, 17), make_move(26, 17)};
  assert(same_move_options(vm, truth, true));
}

void test_king_simple() {
  std::vector<Move> vm, truth;
  Slice bk, wt;

  // black
  bk = wt = 0UL;
  SET_64(bk, 32 + 0);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{
      make_move(0, 4),  make_move(0, 5),  make_move(0, 9), make_move(0, 14),
      make_move(0, 18), make_move(0, 23), make_move(0, 27)};
  assert(same_move_options(vm, truth, true));

  // black
  bk = wt = 0UL;
  SET_64(bk, 32 + 3);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{
      make_move(3, 7),  make_move(3, 10), make_move(3, 14), make_move(3, 17),
      make_move(3, 21), make_move(3, 24), make_move(3, 28)};
  assert(same_move_options(vm, truth, true));

  // black
  bk = wt = 0UL;
  SET_64(bk, 32 + 21);
  vm = valid_moves(bk, wt, true);
  truth =
      std::vector<Move>{make_move(21, 3),  make_move(21, 7),  make_move(21, 10),
                        make_move(21, 12), make_move(21, 14), make_move(21, 16),
                        make_move(21, 17), make_move(21, 24), make_move(21, 25),
                        make_move(21, 28), make_move(21, 30)};
  assert(same_move_options(vm, truth, true));

  // white
  bk = wt = 0UL;
  SET_64(wt, 32 + 3);
  vm = valid_moves(bk, wt, false);
  truth = std::vector<Move>{
      make_move(3, 7),  make_move(3, 10), make_move(3, 14), make_move(3, 17),
      make_move(3, 21), make_move(3, 24), make_move(3, 28)};
  assert(same_move_options(vm, truth, true));
}

void test_king_multiple() {
  std::vector<Move> vm, truth;
  Slice bk, wt;

  bk = wt = 0UL;
  SET_64(bk, 32 + 0);
  SET_64(bk, 32 + 11);
  vm = valid_moves(bk, wt, true);
  truth =
      std::vector<Move>{make_move(11, 2),  make_move(0, 4),  make_move(0, 5),
                        make_move(11, 7),  make_move(0, 9),  make_move(0, 14),
                        make_move(11, 15), make_move(0, 18), make_move(11, 18),
                        make_move(11, 22), make_move(0, 23), make_move(11, 25),
                        make_move(0, 27),  make_move(11, 29)};
  assert(same_move_options(vm, truth, true));
}

void test_king_blocked() {
  std::vector<Move> vm, truth;
  Slice bk, wt;

  // black, own man in the way
  bk = wt = 0UL;
  SET_64(bk, 32 + 0);
  SET_64(bk, 5);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(0, 4), make_move(5, 8), make_move(5, 9)};
  assert(same_move_options(vm, truth, true));

  // black, own man in the way
  bk = wt = 0UL;
  SET_64(bk, 32 + 0);
  SET_64(bk, 9);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(0, 4), make_move(0, 5), make_move(9, 13),
                            make_move(9, 14)};
  assert(same_move_options(vm, truth, true));

  // black, own man in the way
  bk = wt = 0UL;
  SET_64(bk, 32 + 18);
  SET_64(bk, 0);
  SET_64(bk, 15);
  SET_64(bk, 25);
  vm = valid_moves(bk, wt, true);
  truth =
      std::vector<Move>{make_move(0, 4),   make_move(0, 5),   make_move(18, 5),
                        make_move(18, 9),  make_move(18, 14), make_move(15, 19),
                        make_move(18, 22), make_move(18, 23), make_move(18, 27),
                        make_move(25, 29), make_move(25, 30)};
  assert(same_move_options(vm, truth, true));
}

void test_king_capture() {
  std::vector<Move> vm, truth;
  Slice bk, wt;

  // black capturing white, forward
  bk = wt = 0UL;
  SET_64(bk, 32 + 0);
  SET_64(wt, 5);
  SET_64(wt, 6);
  SET_64(wt, 13);
  SET_64(wt, 14);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(0, 9)};
  assert(same_move_options(vm, truth, true));

  // no capturing, just two regular moves
  bk = wt = 0UL;
  SET_64(bk, 32 + 28);
  SET_64(wt, 17);
  SET_64(wt, 14);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(28, 21), make_move(28, 24)};
  assert(same_move_options(vm, truth, true));

  // black capturing white, single option
  bk = wt = 0UL;
  SET_64(bk, 32 + 28);
  SET_64(wt, 17);
  SET_64(wt, 10);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(28, 14)};
  assert(same_move_options(vm, truth, true));
}

void test_king_double_capture() {
  std::vector<Move> vm, truth;
  Slice bk, wt;

  // no capturing, just two regular moves
  bk = wt = 0UL;
  SET_64(bk, 32 + 28);
  SET_64(wt, 24);
  SET_64(wt, 25);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(28, 21)};
  assert(same_move_options(vm, truth, true));

  bk = wt = 0UL;
  SET_64(bk, 32 + 28);
  SET_64(wt, 24);
  SET_64(wt, 5);
  SET_64(wt, 25);
  SET_64(wt, 7);
  vm = valid_moves(bk, wt, true);
  truth = std::vector<Move>{make_move(28, 21), make_move(28, 14),
                            make_move(28, 17), make_move(28, 10)};
  assert(same_move_options(vm, truth, true));
}

void test_draw_rule_723_724_725() {
  Slice bk, wt;

  bk = wt = 0UL;
  SET_64(bk, 32 + 0);
  SET_64(bk, 32 + 3);
  SET_64(bk, 32 + 31);
  SET_64(wt, 32 + 4);

  GameHistory history;
  for (int i = 0; i < 15; ++i) {
    Move mv;
    if (i % 2 == 0) {
      if (i % 4 == 0)
        mv = make_move(3, 7);
      else
        mv = make_move(7, 3);
      do_move_bk(bk, wt, mv);
    } else {
      if (i % 4 == 1)
        mv = make_move(4, 8);
      else
        mv = make_move(8, 4);
      do_move_wt(bk, wt, mv);
    }

    history.update(bk, wt, mv, false);
    assert(history.r723_cnt == i);
    assert(history.r724_cnt == i + 1);
    if (i < 14) assert(!history.is_draw());
  }
  assert(history.is_draw());

  // i == 15, inject a black man to capture in next move
  SET_64(bk, 9);
  Move mv = make_move(9, 13);
  do_move_bk(bk, wt, mv);
  history.update(bk, wt, mv, true);
  assert(history.r723_cnt == 0);
  assert(history.r724_cnt == 16);
  assert(history.r724_cnt == 16);  // 0 really but injection above was illegal
  assert(history.r725_cnt == 0);

  // i == 16
  mv = make_move(8, 17);
  do_move_wt(bk, wt, mv);
  history.update(bk, wt, mv, true);
  assert(history.r723_cnt == 0);
  assert(history.r724_cnt == 17);
  assert(history.r725_cnt == 0);
}

void test_draw_rule_726() {
  Slice bk, wt;

  // --- test 4/5 piece rule
  bk = wt = 0UL;
  SET_64(bk, 32 + 0);
  SET_64(bk, 32 + 3);
  SET_64(bk, 32 + 31);
  SET_64(wt, 32 + 4);

  GameHistory history;
  for (int i = 0; i < 30; ++i) {
    Move mv;
    if (i % 2 == 0) {
      if (i % 4 == 0)
        mv = make_move(3, 7);
      else
        mv = make_move(7, 3);
      do_move_bk(bk, wt, mv);
    } else {
      if (i % 4 == 1)
        mv = make_move(4, 8);
      else
        mv = make_move(8, 4);
      do_move_wt(bk, wt, mv);
    }

    history.update(bk, wt, mv, false);
    assert(history.r726_c45 == i + 1);
    assert(history.r726_c67 == 0);
  }

  auto r726_c45 = history.r726_c45;
  history.reset();
  history.r726_c45 = r726_c45;
  assert(history.is_draw());

  // --- test 6/7 piece rule
  bk = wt = 0UL;
  SET_64(bk, 32 + 0);
  SET_64(bk, 32 + 3);
  SET_64(bk, 32 + 31);
  SET_64(wt, 32 + 4);
  SET_64(wt, 19);
  SET_64(wt, 20);
  SET_64(wt, 27);

  history.reset();
  for (int i = 0; i < 60; ++i) {
    Move mv;
    if (i % 2 == 0) {
      if (i % 4 == 0)
        mv = make_move(3, 7);
      else
        mv = make_move(7, 3);
      do_move_bk(bk, wt, mv);
    } else {
      if (i % 4 == 1)
        mv = make_move(4, 8);
      else
        mv = make_move(8, 4);
      do_move_wt(bk, wt, mv);
    }

    history.update(bk, wt, mv, false);
    assert(history.r726_c45 == 0);
    const auto r726_c67 = history.r726_c67;
    assert(r726_c67 == i + 1);
    history.reset();
    history.r726_c67 = r726_c67;
    assert(!history.is_draw() && i < 59 || history.is_draw());
  }

  // --- test 4/5 and 6/7 piece rule with only 3 pieces => never a draw
  bk = wt = 0UL;
  SET_64(bk, 32 + 0);
  SET_64(bk, 32 + 3);
  SET_64(wt, 32 + 4);

  history.reset();
  for (int i = 0; i < 100; ++i) {
    Move mv;
    if (i % 2 == 0) {
      if (i % 4 == 0)
        mv = make_move(3, 7);
      else
        mv = make_move(7, 3);
      do_move_bk(bk, wt, mv);
    } else {
      if (i % 4 == 1)
        mv = make_move(4, 8);
      else
        mv = make_move(8, 4);
      do_move_wt(bk, wt, mv);
    }

    history.update(bk, wt, mv, false);
    assert(history.r726_c45 == 0);
    assert(history.r726_c67 == 0);
  }

  // --- test 4/5 and 6/7 piece rule with 8 pieces => never a draw
  bk = wt = 0UL;
  SET_64(bk, 32 + 0);
  SET_64(bk, 32 + 3);
  SET_64(bk, 32 + 31);
  SET_64(wt, 32 + 4);
  SET_64(wt, 19);
  SET_64(wt, 20);
  SET_64(wt, 27);
  SET_64(wt, 26);

  history.reset();
  for (int i = 0; i < 100; ++i) {
    Move mv;
    if (i % 2 == 0) {
      if (i % 4 == 0)
        mv = make_move(3, 7);
      else
        mv = make_move(7, 3);
      do_move_bk(bk, wt, mv);
    } else {
      if (i % 4 == 1)
        mv = make_move(4, 8);
      else
        mv = make_move(8, 4);
      do_move_wt(bk, wt, mv);
    }

    history.update(bk, wt, mv, false);
    assert(history.r726_c45 == 0);
    assert(history.r726_c67 == 0);
  }
}

void _helper_727_728(Slice bk, Slice wt, bool is_727) {
  GameHistory history;
  for (int i = 0; i < 5; ++i) {
    Move mv;
    if (i % 2 == 0) {
      if (i % 4 == 0)
        mv = make_move(0, 5);
      else
        mv = make_move(5, 0);
      do_move_bk(bk, wt, mv);
    } else {
      if (i % 4 == 1)
        mv = make_move(3, 28);
      else
        mv = make_move(28, 3);
      do_move_wt(bk, wt, mv);
    }

    history.update(bk, wt, mv, false);
    if (is_727) {
      assert(history.r727_cnt == i + 1);
      const auto r727_cnt = history.r727_cnt;
      history.reset();
      history.r727_cnt = r727_cnt;
    } else {
      assert(history.r728_cnt == i + 1);
      const auto r728_cnt = history.r728_cnt;
      history.reset();
      history.r728_cnt = r728_cnt;
    }
    assert(!history.is_draw() && i < 4 || history.is_draw());
  }
}

void test_draw_rule_727() {
  Slice bk, wt;

  // three kings vs. king
  bk = wt = 0UL;
  SET_64(wt, 32 + 3);
  SET_64(bk, 32 + 0);
  SET_64(bk, 32 + 30);
  SET_64(bk, 32 + 31);
  _helper_727_728(bk, wt, true);

  // two kings, one man vs. king
  CLEAR_64(bk, 32 + 30);
  SET_64(bk, 30);
  _helper_727_728(bk, wt, true);

  // one king, two men vs. king
  CLEAR_64(bk, 32 + 31);
  SET_64(bk, 31);
  _helper_727_728(bk, wt, true);
}

void test_draw_rule_728() {
  Slice bk, wt;

  // two kings vs. king
  bk = wt = 0UL;
  SET_64(wt, 32 + 3);
  SET_64(bk, 32 + 0);
  SET_64(bk, 32 + 31);
  _helper_727_728(bk, wt, false);

  // one king, one man vs. king
  CLEAR_64(bk, 32 + 31);
  SET_64(bk, 31);
  _helper_727_728(bk, wt, false);

  // one king, two men vs. king
  CLEAR_64(bk, 31);
  _helper_727_728(bk, wt, false);
}

void test_minimax() {
  Slice bk, wt;
  bool blacks_turn;
  //   random_board(bk, wt);

  bk = 15822;
  wt = 6305742848;
  blacks_turn = 0;
  print_board(bk, wt);

  //   auto moves = valid_moves(bk, wt, false, 0);
  auto moves = valid_capturing_moves_from(bk, wt, 0);
  printf("%lu valid move(s):\n", moves.size());
  for (auto mv : moves) printf("%lu -> %lu\n", get_from(mv), get_to(mv));

  // const Move move = minimax_strategy(bk, wt, false, NO_LOC, 3);
  // printf("selected move: %s\n", to_string(move).c_str());
}

void test_shared_arg_sort() {
  vector<double> xs{2.34345, 5.23423, -4.4, 0.0};

  auto ys = arg_sort(xs, true);
  assert(ys == vector<size_t>({2, 3, 0, 1}));

  ys = arg_sort(xs, false);
  assert(ys == vector<size_t>({1, 0, 3, 2}));
}

void test_all() {
  // make sure assertions are enabled
  bool enabled = false;
  assert(enabled = true);
  if (!enabled)
    throw runtime_error("Error: Assertions must be enabled when testing!");

  test_valid_moves();
  test_valid_capturing_moves_from();
  test_do_move();
  test_rotate_slice();
  test_get_set();
  test_make_move();
  test_one_more();
  test__can_king_capture_along_beam_ne();
  test__can_king_capture_from();
  test_men_simple();
  test_men_multiple();
  test_men_capture();
  test_king_simple();
  test_king_multiple();
  test_king_blocked();
  test_king_capture();
  test_king_double_capture();
  test_draw_rule_723_724_725();
  test_draw_rule_726();
  test_draw_rule_727();
  test_draw_rule_728();
  //   test_minimax();
  test_shared_arg_sort();

  printf("All tests passed\n");
}

}  // namespace shashki
