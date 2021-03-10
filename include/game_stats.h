#pragma once

#include <cstdint>
#include <string>
#include "game.h"

namespace shashki {

/**
 * Mutable structure to collect simple stats on multiple games
 */
struct GameStats {
  GameStats()
      : bk_wins(0), wt_wins(0), draws(0), n_games(0), n_plies(0) { /* empty */
  }

  void update(const GameResult& res) {
    if (res.status == GameStatus::BLACK_WINS) {
      ++bk_wins;
    } else if (res.status == GameStatus::WHITE_WINS) {
      ++wt_wins;
    } else if (res.status == GameStatus::DRAW) {
      ++draws;
    } else
      throw std::runtime_error("Unexpected status, game is supposed to be over!");

    n_plies += res.n_plies;
    ++n_games;
  }

  // counts how many times black, white, or neither won, respectively
  uint_fast64_t bk_wins, wt_wins, draws;

  // total number of games played
  uint64_t n_games;

  // total number of plies played across all games
  uint64_t n_plies;
};

std::string to_string(const GameStats& stats);

}  // namespace shashki
