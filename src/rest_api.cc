#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <regex>
#include "board.h"
#include "game.h"
#include "nlohmann/json.hpp"

using namespace Pistache;
using namespace std;
using json = nlohmann::json;

namespace shashki {

static Rest::Router router;
static const regex digits_only(R"(\d+)");

// strategy regex, cf. start_rest_server() in rest_api.h
static const regex re_random_strategy(R"(random)");
static const regex re_negamax_ab_strategy(R"(negamax-ab,(\d+))");

// attempts to parse `s` as unsigned long int, throws if that fails
uint_fast64_t _parse_ul(const string& s) {
  if (regex_match(s, digits_only)) return stoul(s);
  throw runtime_error("Not an integer: " + s);
}

void _parse_query(const Http::Uri::Query& query, Slice& bk, Slice& wt,
                  bool& blacks_turn, string& strategy, Loc& capfrom,
                  bool& explain) {
  if (!(query.has("bk")))
    throw runtime_error("Bad query, parameter 'bk' is missing");
  if (!(query.has("wt")))
    throw runtime_error("Bad query, parameter 'wt' is missing");
  if (!(query.has("player")))
    throw runtime_error("Bad query, parameter 'player' is missing");

  try {
    bk = _parse_ul(query.get("bk").get());
    wt = _parse_ul(query.get("wt").get());

    if (!board_valid(bk, wt)) throw runtime_error("Board is invalid");

    const string& p = query.get("player").get();
    if (p == "bk")
      blacks_turn = true;
    else if (p == "wt")
      blacks_turn = false;
    else
      throw runtime_error("Bad query, player must be 'bk' or 'wt'");

    strategy = query.get("strat").getOrElse("minimax,5");

    capfrom = NO_LOC;
    if (query.has("capfrom")) capfrom = _parse_ul(query.get("capfrom").get());

    explain = false;
    if (query.has("explain")) {
      explain = query.get("explain").get() == "true";
      if (!explain && query.get("explain").get() != "false")
        throw runtime_error("Bad query, explain must be 'true' or 'false'");
    }
  } catch (exception& e) {
    throw runtime_error(e.what());
  }
}

// moves need cleaning in order not to confuse the endpoint client; the unused
// bits in every move are undefined by convention
void _clean_moves(std::vector<Move>& moves) {
  for (Move& m : moves) m = make_move(get_from(m), get_to(m));
}

// for endpoint definition see start_rest_server(), in rest_api.h
void _v1_best(const Rest::Request& request, Http::ResponseWriter response) {
  const auto& query = request.query();

  try {
    // parse query string
    Slice bk, wt;
    bool blacks_turn;
    string strat;
    Loc capfrom;
    bool explain;
    _parse_query(query, bk, wt, blacks_turn, strat, capfrom, explain);

    printf(
        "\n\n================================\nQuery: /moves/best: bk=%lu, "
        "wt=%lu, player=%s strat=%s "
        "capfrom=%lu\n",
        bk, wt, blacks_turn ? "bk" : "wt", strat.c_str(), capfrom);

    // make sure we have valid moves available
    if (valid_moves(bk, wt, blacks_turn).empty())
      throw runtime_error("There's no valid move for " +
                          string(blacks_turn ? "black" : "white"));

    // parse strategy
    smatch matches;
    Strategy strategy;
    nlohmann::json explanation;

    // Random
    if (regex_match(strat, matches, re_random_strategy)) {
      strategy = random_strategy;
    }
    // Negamax α-β
    else if (regex_match(strat, matches, re_negamax_ab_strategy)) {
      const uint_fast8_t depth = _parse_ul(matches[1].str());
      strategy = bound_negamax_ab_strategy(depth, vfunc_external_1,
                                           explain ? &explanation : nullptr);
    }
    // invalid arg
    else {
      throw runtime_error("Invalid strategy (param `strat`): " + strat);
    }

    print_board(bk, wt, vector<Move>());

    // run strategy
    const clock_t& tic = clock();
    GameHistory history;
    GameStatus status = play_a_ply(bk, wt, blacks_turn, history, &strategy);
    vector<Move> moves(history.get_trajectory());
    const double& cpu_time = double(clock() - tic) / CLOCKS_PER_SEC;

    _clean_moves(moves);

    printf("After playing the returned moves:\n");
    print_board(bk, wt, vector<Move>(), &moves.front());

    // send response
    // printf("explanation: %s\n", explanation.dump(2).c_str());
    const json& resp = {{"strat", strat},
                        {"moves", moves},
                        {"moveTime", cpu_time},
                        {"explanation", explanation}};
    response.setMime(MIME(Text, Json));
    response.headers().add<Http::Header::AccessControlAllowOrigin>("*");
    response.send(Http::Code::Ok, resp.dump());
    // resp.erase("explanation");
    // printf("REST: Request OK: %s\n", resp.dump().c_str());
    printf("Request completed in %.6f sec\n", cpu_time);
  } catch (runtime_error& e) {
    printf("REST error: %s\n", e.what());
    response.headers().add<Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Bad_Request, e.what());
  }
}

// for endpoint definition see start_rest_server(), in rest_api.h
void _v1_all(const Rest::Request& request, Http::ResponseWriter response) {
  static size_t call_cnt = 0;
  ++call_cnt;

  const auto& query = request.query();

  try {
    const clock_t& tic = clock();

    // parse query string
    Slice bk, wt;
    bool blacks_turn;
    string strat;
    Loc capfrom;
    bool explain;
    _parse_query(query, bk, wt, blacks_turn, strat, capfrom, explain);
    if (explain) throw runtime_error("Not implemented: explain must be false");

    if (capfrom != NO_LOC)
      printf("WARNING: capfrom must not be present for /moves/all");

    // find valid moves
    auto moves = valid_moves(bk, wt, blacks_turn);
    const double& cpu_time = double(clock() - tic) / CLOCKS_PER_SEC;

    _clean_moves(moves);

    // send response
    const json& resp = {{"moves", moves}, {"cpuTimeSec", cpu_time}};
    response.setMime(MIME(Text, Json));
    response.headers().add<Http::Header::AccessControlAllowOrigin>("*");
    response.send(Http::Code::Ok, resp.dump());
  } catch (runtime_error& e) {
    response.headers().add<Http::Header::AccessControlAllowOrigin>("*");
    response.send(Pistache::Http::Code::Bad_Request, e.what());
  }
}

void start_rest_server(shared_ptr<Pistache::Http::Endpoint>& endpoint,
                       const uint16_t& port, const int threads) {
  // create endpoint
  endpoint = make_shared<Http::Endpoint>(Address(Ipv4::any(), port));
  endpoint->init(Http::Endpoint::options()
                     .threads(static_cast<int>(threads))
                     .flags(Tcp::Options::ReuseAddr));  // avoid address in use

  // register routes
  Rest::Routes::Get(router, "/v1/moves/best", Rest::Routes::bind(&_v1_best));
  Rest::Routes::Get(router, "/v1/moves/all", Rest::Routes::bind(&_v1_all));
  endpoint->setHandler(router.handler());

  // begin serving, blocking the current thread
  printf(
      "Shashki game server running, %d thread(s), listening on port %d"
      " (Ctrl+C to exit)\n",
      threads, port);

  endpoint->serve();  // blocking
}

}  // namespace shashki
