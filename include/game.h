#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include "board.h"
#include "game_history.h"
#include "strategies.h"
#include "tests.h"

namespace shashki {

// play `n` random games and print stats
void time_game(int n = 100000);

// Game status with obvious meanings; first three are terminal
enum class GameStatus { BLACK_WINS, WHITE_WINS, DRAW, IN_PROGRESS };

// Data class for the result of a game
struct GameResult {
  const GameStatus status;
  const uint_fast16_t n_plies;

  GameResult(GameStatus status, uint_fast64_t n_plies)
      : status(status), n_plies(n_plies) { /* empty */
  }
};

/**
 * Play an the game with two competeting strategies until termination
 *
 * The initial board with black on top is bk == 4095UL, wt == 4095UL << 20
 */
GameResult play_to_end(const Strategy& bk_strategy, const Strategy& wt_strategy,
                       Slice& bk, Slice& wt, bool blacks_turn);

/**
 * Play a single ply of game. Note that in the case of captures this may involve
 * more than one move
 */
GameStatus play_a_ply(Slice& bk, Slice& wt, const bool blacks_turn,
                      GameHistory& history, const Strategy* strategy);

}  // namespace shashki
