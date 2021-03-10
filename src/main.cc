#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "board.h"
#include "contest.h"
#include "game.h"
#include "rest_api.h"
#include "tests.h"

using namespace shashki;
using namespace std;

// pointer to REST endpoint (if any)
static std::shared_ptr<Pistache::Http::Endpoint> endpoint;

// gets called upon Ctrl+C
void _ctrl_c_handler(int) {
  if (endpoint != nullptr) {
    endpoint->shutdown();
    printf("\nServer shut down, goodbye\n\n");
  }
  exit(0);
}

int main(int argc, char* argv[]) {
  if (argc > 1 && string(argv[1]) == "serve") {
    signal(SIGINT, _ctrl_c_handler);
    start_rest_server(endpoint, 9080);
  } else if (argc > 1 && string(argv[1]) == "time")
    time_game();
  else if (argc > 1 && string(argv[1]) == "test")
    test_all();
  else if (argc > 1 && string(argv[1]) == "contest") {
    auto stats = run_contest(bound_negamax_ab_strategy(6, vfunc_basic),
                             bound_negamax_ab_strategy(6, vfunc_basic), 100);
    printf("%s\n", to_string(stats).c_str());
  } else if (argc > 1 && string(argv[1]) == "explain") {
    Slice bk = 110190UL, wt = 1979449344UL;
    print_board(bk, wt);
    int color = 1;
    uint_fast8_t depth = 3;
    nlohmann::json explain;
    Move best_move = negamax_ab_strategy(bk, wt, color == 1, NO_LOC, depth,
                                         vfunc_basic, &explain);

    printf("explanation: %s\n", explain.dump(2).c_str());
  } else if (argc > 1 && string(argv[1]) == "print") {
    if (argc != 4) {
      printf("Usage: %s print (bk) (wt)\n\n", argv[0]);
      return 1;
    }
    print_board(stoull(argv[2]), stoull(argv[3]));
  } else
    printf("Usage: %s (serve|time|test|contest|print)\n\n", argv[0]);

  return 0;
}
