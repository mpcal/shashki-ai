#pragma once

#include <cstdint>
#include "board.h"

namespace shashki {

// accumulated history over an entire game, used to detect draws
struct GameHistory {
  GameHistory() { reset(); }

  // returns true if the game is a draw and false otherwise
  bool update(const Slice& bk, const Slice& wt, const Move& mv,
              const bool& capture) {
    // counts = # bk men, # bk kings, # wt men, # wt kings
    const uint_fast8_t& bk_m = __builtin_popcount(get_men_32(bk));
    const uint_fast8_t& bk_k = __builtin_popcount(get_kings_32(bk));
    const uint_fast8_t& wt_m = __builtin_popcount(get_men_32(wt));
    const uint_fast8_t& wt_k = __builtin_popcount(get_kings_32(wt));
    const uint_fast8_t& n_tokens = bk_m + bk_k + wt_m + wt_k;

    // used in an additional rule that limits the total number of moves by
    // requiring move_cnt < MAX_MOVES
    ++move_cnt;

    trajectory.push_back(mv);

    // rule 7.2.3: approximated with number of rounds in which the total token
    // count did not change
    if (prev_bk_m == bk_m && prev_bk_k == bk_k && prev_wt_m == wt_m &&
        prev_wt_k == wt_k)
      ++r723_cnt;
    else
      r723_cnt = 0;

    // rule 7.2.4
    r724_cnt += wt_m == 0 && bk_k >= 3 && wt_k == 1 ||
                bk_m == 0 && wt_k >= 3 && bk_k == 1;

    // rule 7.2.5
    const Loc& to = get_to(mv);
    if (!capture && (GET_64(bk, to + 32) || GET_64(wt, to + 32)))
      ++r725_cnt;
    else
      r725_cnt = 0;

    // rule 7.2.6
    if (!capture && n_tokens <= 7 && bk_k && wt_k &&
        (bk_k == prev_bk_k && wt_k == prev_wt_k || move_cnt == 1)) {
      if (n_tokens == 4 || n_tokens == 5)
        ++r726_c45;
      else if (n_tokens == 6 || n_tokens == 7)
        ++r726_c67;
      else
        r726_c45 = r726_c67 = 0;
    } else
      r726_c45 = r726_c67 = 0;

    // rule 7.2.7
    // 287458440 = value of a 32-bit int when all bits on main diagonal of a
    //             shashki::Slice are set
    r727_cnt += (get_kings_32(bk) & 287458440U) && bk_k == 1 && bk_m == 0 &&
                    (wt_k == 3 && wt_m == 0 || wt_k == 2 && wt_m == 1 ||
                     wt_k == 1 && wt_m == 2) ||
                // or vice versa:
                (get_kings_32(wt) & 287458440U) && wt_k == 1 && wt_m == 0 &&
                    (bk_k == 3 && bk_m == 0 || bk_k == 2 && bk_m == 1 ||
                     bk_k == 1 && bk_m == 2);

    // rule 7.2.8
    r728_cnt += bk_k == 1 && (wt_k == 2 || wt_k == 1 && wt_m <= 1) ||
                // or vice versa:
                wt_k == 1 && (bk_k == 2 || bk_k == 1 && bk_m <= 1);

    // remember previous values
    prev_bk_m = bk_m;
    prev_bk_k = bk_k;
    prev_wt_m = wt_m;
    prev_wt_k = wt_k;

    return is_draw();
  }

  // returns the current number of moves registered
  inline int_fast16_t moves() { return move_cnt; }

  // returns true if game is a draw
  inline bool is_draw() {
    return move_cnt > MAX_TOTAL_MOVES || r723_cnt > MAX_MOVES_NO_CHANGE ||
           r724_cnt > 15 || r725_cnt >= 15 || r726_c45 >= 30 ||
           r726_c67 >= 60 || r727_cnt >= 5 || r728_cnt >= 5;
  }

  // resets all counters
  inline void reset() {
    move_cnt = prev_bk_m = prev_bk_k = prev_wt_m = prev_wt_k = r723_cnt =
        r724_cnt = r725_cnt = r726_c45 = r726_c67 = r727_cnt = r728_cnt = 0;
    trajectory.clear();
    trajectory.reserve(96);
  }

  const std::vector<Move>& get_trajectory() const { return trajectory; }

  // inspired by std::to_string
  friend std::string to_string(const GameHistory&);

  // test functions will need referential access to private members. i know,
  // spaghetti, but I find it preferable to tie this class and its testing
  // functions together rather than exposing member variables only for testing
  friend void test_draw_rule_723_724_725();
  friend void test_draw_rule_726();
  friend void test_draw_rule_727();
  friend void _helper_727_728(Slice, Slice, bool);
  friend void test_draw_rule_728();

  static constexpr uint_fast16_t MAX_TOTAL_MOVES = 1000;
  static constexpr uint_fast16_t MAX_MOVES_NO_CHANGE = 60;

 private:
  uint_fast16_t move_cnt;  // proxy for move number
  uint_fast8_t prev_bk_m;  // value of bk_m after previous update() call
  uint_fast8_t prev_bk_k;  // value of bk_k after previous update() call
  uint_fast8_t prev_wt_m;  // value of wt_m after previous update() call
  uint_fast8_t prev_wt_k;  // value of wt_k after previous update() call

  uint_fast8_t r723_cnt;  // #moves where condition of rule 7.2.3 was true
  uint_fast8_t r724_cnt;  // #moves where condition of rule 7.2.4 was true
  uint_fast8_t r725_cnt;  // #moves where condition of rule 7.2.5 was true
  uint_fast8_t r726_c45;  // rule 7.2.6: #moves where 4- or 5-condition was true
  uint_fast8_t r726_c67;  // rule 7.2.6: #moves where 6- or 7-condition was true
  uint_fast8_t r727_cnt;  // #moves where condition of rule 7.2.7 was true
  uint_fast8_t r728_cnt;  // #moves where condition of rule 7.2.8 was true

  std::vector<Move> trajectory;  // all the moves, latest is at the back
};

std::string to_string(const GameHistory&);

}  // namespace shashki
