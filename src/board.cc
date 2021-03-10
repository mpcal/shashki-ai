#include <stdint.h>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include "_board_internal.h"
#include "game.h"
#include "game_stats.h"

using namespace std;

namespace shashki {

static random_device r;
static seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
static mt19937 eng(seed);
uniform_real_distribution<> uniform(0., 1.);

// look-up table for reversing bits in a word, cf. https://cutt.ly/LjxpWMK
static const unsigned char bit_reverse_table_256[256] = {
#define R2(n) n, n + 2 * 64, n + 1 * 64, n + 3 * 64
#define R4(n) R2(n), R2(n + 2 * 16), R2(n + 1 * 16), R2(n + 3 * 16)
#define R6(n) R4(n), R4(n + 2 * 4), R4(n + 1 * 4), R4(n + 3 * 4)
    R6(0), R6(2), R6(1), R6(3)};

string to_string(const Move &mv) {
  char buf[32];
  sprintf(buf, "%2lu -> %2lu", get_from(mv), get_to(mv));
  return string(buf);
}

Slice rotate_slice(const Slice &slice) {
  Slice value;

  unsigned char *p = (unsigned char *)&slice;
  unsigned char *q = (unsigned char *)&value;

  // lower four bytes (men)
  q[3] = bit_reverse_table_256[p[0]];
  q[2] = bit_reverse_table_256[p[1]];
  q[1] = bit_reverse_table_256[p[2]];
  q[0] = bit_reverse_table_256[p[3]];

  // upper four bytes (kings)
  q[7] = bit_reverse_table_256[p[4]];
  q[6] = bit_reverse_table_256[p[5]];
  q[5] = bit_reverse_table_256[p[6]];
  q[4] = bit_reverse_table_256[p[7]];

  return value;
}

Slice flip_slice(const Slice &slice) {
  Slice value = 0UL;

  value |= (slice & 0xf) << 28;
  value |= (slice & 0xf0) << 20;
  value |= (slice & 0xf00) << 12;
  value |= (slice & 0xf000) << 4;
  value |= (slice & 0xf0000) >> 4;
  value |= (slice & 0xf00000) >> 12;
  value |= (slice & 0xf000000) >> 20;
  value |= (slice & 0xf0000000) >> 28;

  return value;
}

bool board_valid(const Slice &bk, const Slice &wt) {
  // max 12 tokens/player
  if (__builtin_popcountl(bk) > 12 || __builtin_popcountl(wt) > 12) {
    printf("Invalid board: too many tokens\n");
    return false;
  }

  // no spot occupied twice
  const Slice &bk_and_wt = bk & wt;
  if (__builtin_popcountl(bk_and_wt) > 0 ||
      __builtin_popcount(get_men_32(bk_and_wt) & get_kings_32(bk_and_wt)) > 0) {
    printf("Invalid board: double occupancy\n");
    return false;
  }

  return true;
}

void print_board(const Slice &bk, const Slice &wt, const vector<Move> &options,
                 const Move *const highlight) {
  const auto COLOR_BLK = "\e[1;30m";
  const auto COLOR_WHT = "\e[0;37m";
  const auto COLOR_HWHT = "\e[0;97m";
  const auto COLOR_GREEN = "\e[1;92m";
  const auto COLOR_RESET = "\e[0m";

  const Slice is_empty = ~((bk >> 32) | bk | (wt >> 32) | wt);

  // options for the next move
  Slice opt = 0UL;
  for (const auto &m : options) SET_64(opt, get_to(m));

  Slice opt_high = 0UL;
  if (highlight) {
    SET_64(opt_high, get_from(*highlight));
    SET_64(opt_high, get_to(*highlight));
  }

  printf("Board bk=%lu wt=%lu score(for bk)=%d score(for wt)=%d\n", bk, wt,
         vfunc_basic(bk, wt, true, 0), vfunc_basic(bk, wt, false, 0));
  for (int i = 0; i < 8; ++i) {
    printf("  ");
    if (i % 2 == 0) printf("   ");

    // board
    for (int j = 0; j < 4; ++j) {
      const int ix = 4 * i + j;
      if (GET_64(opt_high, ix))
        printf(COLOR_GREEN);
      else
        printf(COLOR_HWHT);

      if (GET_64(bk, ix))
        printf("□     ");
      else if (GET_64(wt, ix))
        printf("■     ");
      else if (GET_64(bk, 32 + ix))
        printf("△     ");
      else if (GET_64(wt, 32 + ix))
        printf("▲     ");
      else if (GET_64(opt_high, ix)) {
        printf(COLOR_GREEN);
        printf("✘     ");
      } else if (GET_64(opt, ix)) {
        printf(COLOR_WHT);
        printf("✘     ");
      } else {
        printf(COLOR_BLK);
        printf("·     ");
      }
    }
    if (i % 2 != 0) printf("   ");

    // bit indices
    printf("  ");
    if (i % 2 == 0) {
      printf("    ");
    }
    for (int j = 0; j < 4; ++j) {
      const int ix = 4 * i + j;
      if (GET_64(is_empty, ix))
        printf(COLOR_BLK);
      else
        printf(COLOR_HWHT);

      printf("%2d  ", i * 4 + j);
      if (j < 3 || i % 2) printf("    ");
    }

    printf("\n");
    printf(COLOR_RESET);
  }

  // reset magic (some kinda color stack behind?!); not investigating further
  // since speed is not of concern for this function anyways
  for (int i = 0; i < 256; ++i) printf(COLOR_RESET);
}

void random_board(Slice &bk, Slice &wt, double p_skip_token, double p_is_king) {
  std::vector<uint_fast8_t> perm(32);
  std::iota(perm.begin(), perm.end(), 0);
  std::shuffle(perm.begin(), perm.end(), eng);
  perm.erase(perm.begin() + 24, perm.end());

  bk = wt = 0;
  for (int i = 0; i < perm.size(); ++i) {
    if (uniform(eng) < p_skip_token) continue;
    bool king = uniform(eng) < p_is_king;
    SET_64(i < perm.size() / 2 ? wt : bk, perm[i] + king * 32);
  }
}

}  // namespace shashki
