#include "game.h"
#include "board.h"

using namespace std;

namespace shashki {

GameStatus play_a_ply(Slice& bk, Slice& wt, const bool blacks_turn,
                      GameHistory& history, const Strategy* strategy) {

  Move move = strategy->operator()(bk, wt, blacks_turn, NO_LOC);

  if (move == NO_MOVE)
    // Game over, no more moves for the current player
    return blacks_turn ? GameStatus::WHITE_WINS : GameStatus::BLACK_WINS;

  bool captured = do_move(bk, wt, move);
  if (history.update(bk, wt, move, captured)) return GameStatus::DRAW;

  if (captured)
    for (;;) {
      move = strategy->operator()(bk, wt, blacks_turn, get_to(move));
      if (move == NO_MOVE) break;

      captured = do_move(bk, wt, move);
      if (history.update(bk, wt, move, captured))
        return GameStatus::DRAW;
    }

  return GameStatus::IN_PROGRESS;
}

GameResult play_to_end(const Strategy& bk_strategy, const Strategy& wt_strategy,
                       Slice& bk, Slice& wt, bool blacks_turn) {
  GameHistory history;

  for (auto plies = 1;; ++plies) {
    GameStatus status = play_a_ply(bk, wt, blacks_turn, history,
                                   blacks_turn ? &bk_strategy : &wt_strategy);
    if (status != GameStatus::IN_PROGRESS)
      return GameResult(status, plies);

    blacks_turn = !blacks_turn;
  }
}

void time_game(int n_games) {
  Slice bk, wt;

  uint_fast64_t n_moves = 0;
  uint_fast64_t move_cnt;

  clock_t begin = clock();
  for (int i = 0; i < n_games; ++i) {
    bk = 4095UL;
    wt = 4095UL << 20;

    const GameResult& res =
        play_to_end(random_strategy, random_strategy, bk, wt, false);
    n_moves += res.n_plies;
  }
  clock_t end = clock();

  double elapsed = double(end - begin) / CLOCKS_PER_SEC;
  printf("Played %lu moves in %d games (%.1f moves/game)\n", n_moves, n_games,
         (double)n_moves / n_games);
  printf("Elapsed %.3f s (%.3f μs/game, %.0f games/s)\n", elapsed,
         1e6 * elapsed / n_games, 1 / elapsed * n_games);
}

}  // namespace shashki
