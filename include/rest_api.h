#pragma once

#include <pistache/endpoint.h>
#include <cstdint>

namespace shashki {

/**
 * Starts the REST server, will block calling thread
 *
 * E.g.
 * localhost:9080/v1/moves/best/?bk=597484&wt=3619815424&player=wt&strat=minimax,2
 *
 * Endpoint
 * /v1/moves/(best|all)?bk=<uint64>&wt=<uint64>&player=<bk|wt>(&strat=<strat>|)(capfrom=<uint64>|)(tag=<string>|)
 * - bk: black's board, 64-bit unsigned int, cf. board.h
 * - wt: white's board, 64-bit unsigned int, cf. board.h
 * - player: bk or wt, indicating who's turn it is
 * - strat (optional, default='minimax,5', only relevant for /v1/moves/best):
 *   - 'random': pick a random move
 *   - 'negamax-ab,<depth>': game tree search with pruning, down to depth `depth`
 * - capfrom: index where to start the move; finds only capturing moves;  must
 *   be consistent with player; will find
 * - tag: any optional string, mostly used for debugging
 *
 * - best: finds best move
 * - all: finds all valid moves
 *
 * Returns the endpoint through the first argument. For a clean exit, the caller
 * should invoke shutdown() on the returned object
 */
void start_rest_server(std::shared_ptr<Pistache::Http::Endpoint>& endpoint,
                       const uint16_t& port = 9080, const int threads = 1);

}  // namespace shashki
