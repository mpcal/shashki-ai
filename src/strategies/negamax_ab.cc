#include <random>
#include "game.h"
#include "game_history.h"
#include "shared.h"
#include "strategies.h"
#include "valuation.h"

using namespace std;
using json = nlohmann::json;

namespace shashki {

// count number of value function evals
static thread_local uint_fast64_t n_evals;

// stores the top level move-value pairs, useful to explain the choice or do
// soft move selection
static thread_local vector<pair<Move, int>> _root_moves;

void _get_capture_endpoints_helper(const Slice& bk, const Slice& wt,
                                   const Loc& from,
                                   vector<pair<Slice, Slice>>& buf) {
  // collect all *capturing* moves
  const auto& moves = valid_capturing_moves_from(bk, wt, from);

  if (moves.empty())
    buf.push_back(make_pair<>(bk, wt));
  else {
    for (const Move& mv : moves) {
      Slice _bk(bk), _wt(wt);
      do_move(_bk, _wt, mv);
      _get_capture_endpoints_helper(_bk, _wt, get_to(mv), buf);
    }
  }
}

static vector<pair<Slice, Slice>> _get_capture_endpoints(const Slice& bk,
                                                         const Slice& wt,
                                                         const Loc& from) {
  vector<pair<Slice, Slice>> value;
  _get_capture_endpoints_helper(bk, wt, from, value);
  return value;
}

/**
 * Returns the optimal score of the current depth
 *
 * - best_move: output variable for best move
 *
 * NOTE:
 * color == 1 <-> blacks_turn == true; also, value_estim(.) must be compatible
 * and return how favorable the move is for *black*
 */
static int _negamax_ab(const Slice& bk, const Slice& wt,
                       const uint_fast8_t& remaining_depth, int alpha,
                       const int beta, const int color, Move& best_move,
                       const ValueEstimator& value_estim,
                       const Loc& capture_from,
                       const uint_fast8_t cur_depth = 0) {
  const bool blacks_turn = color == 1;
  assert(blacks_turn || color == -1);

  // check for termination of recursion
  vector<Move> moves;
  if (capture_from == NO_LOC)
    moves = valid_moves(bk, wt, blacks_turn);
  else
    moves = valid_capturing_moves_from(bk, wt, capture_from);

  if (remaining_depth == 0 || moves.empty()) {
    ++n_evals;
    return color * value_estim(bk, wt, blacks_turn, cur_depth);
  }

  int value = -2050505050;
  for (int i = 0; i < (int)moves.size(); ++i) {
    const Move& mv = moves[i];

    // execute the move
    Slice _bk(bk), _wt(wt);
    const bool capture = do_move(_bk, _wt, mv);

    // find all continuation points after this move, possibly just the current
    // one (_bk, _wt)
    vector<pair<Slice, Slice>> endpoints;
    if (capture) {
      endpoints = _get_capture_endpoints(_bk, _wt, get_to(mv));
      assert(!endpoints.empty());
    } else
      endpoints = vector<pair<Slice, Slice>>{make_pair<>(_bk, _wt)};

    // continue search
    int val = -2070707070;
    for (const auto& [__bk, __wt] : endpoints) {
      int v =
          -_negamax_ab(__bk, __wt, remaining_depth - 1, -beta, -alpha, -color,
                       best_move, value_estim, NO_LOC, cur_depth + 1);
      val = max(val, v);
    }

    if (cur_depth == 0) _root_moves.push_back(make_pair(mv, val));

    if (val > value) {
      value = val;
      if (cur_depth == 0) best_move = mv;
    }

    alpha = max(alpha, value);
    if (alpha >= beta) {
      break;
    }
  }

  return value;
}

// same as _negamax_ab() but with explaination; mostly for debugging but keep
// the two in-line anyways
static int _negamax_ab_explained(const Slice& bk, const Slice& wt,
                                 const uint_fast8_t& remaining_depth, int alpha,
                                 const int beta, const int color,
                                 Move& best_move,
                                 const ValueEstimator& value_estim,
                                 json& explanation,
                                 const uint_fast8_t cur_depth = 0) {
  const bool blacks_turn = color == 1;
  assert(blacks_turn || color == -1);

  // check for termination of recursion
  vector<Move> moves = valid_moves(bk, wt, blacks_turn);
  if (remaining_depth == 0 || moves.empty()) {
    ++n_evals;
    return color * value_estim(bk, wt, blacks_turn, cur_depth);
  }

  json child_explanations = json::array();

  int value = -2060606060;
  for (int i = 0; i < (int)moves.size(); ++i) {
    const Move& mv = moves[i];

    // execute the move
    Slice _bk(bk), _wt(wt);
    do_move(_bk, _wt, mv);

    // find all continuation points after this move, possibly just the current
    // one (_bk, _wt)
    auto endpoints = _get_capture_endpoints(_bk, _wt, get_to(mv));

    json child_expl = {
        {"bk", std::to_string(_bk)},
        {"wt", std::to_string(_wt)},
    };

    // continue search
    int val = -2070707070;
    for (const auto& [__bk, __wt] : endpoints) {
      int v = -_negamax_ab_explained(__bk, __wt, remaining_depth - 1, -beta,
                                     -alpha, -color, best_move, value_estim,
                                     child_expl, cur_depth + 1);
      val = max(val, v);
    }

    if (cur_depth == 0) _root_moves.push_back(make_pair(mv, val));

    if (val > value) {
      value = val;
      if (cur_depth == 0) best_move = mv;
    }

    child_expl["score"] = val;
    child_expl["best"] = value;
    child_expl["pruned"] = false;
    child_expl["alpha"] = alpha;
    child_expl["beta"] = beta;
    child_expl["child_ix"] = i;
    child_explanations.push_back(child_expl);

    alpha = max(alpha, value);
    if (alpha >= beta) {
      // insert pruned children into explanation
      for (int j = i + 1; j < (int)moves.size(); ++j) {
        const Move& mv2 = moves[j];
        Slice _bk(bk), _wt(wt);
        do_move(_bk, _wt, mv2);  // ignore capturing, will be pruned anyways
        child_expl = {{"bk", std::to_string(_bk)},
                      {"wt", std::to_string(_wt)},
                      {"score", -123456789},  // anything, since pruned
                      {"best", value},
                      {"child_ix", j},
                      {"pruned", true}};
        child_explanations.push_back(child_expl);
      }

      break;  // cut-off
    }
  }

  explanation["bk"] = std::to_string(bk);
  explanation["wt"] = std::to_string(wt);
  explanation["score"] = value;
  explanation["alpha"] = alpha;
  explanation["beta"] = beta;
  explanation["bk_turn"] = blacks_turn;
  explanation["children"] = child_explanations;

  return value;
}

// choose element with a proba proportinal to its (descending) rank,
// that is, pick largest element with proba
static size_t pick_best_ix(const vector<int>& scores) {
  assert(!scores.empty());
  if (scores.size() == 1) return 0;

  random_device r;
  seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
  shared_ptr<mt19937> eng = make_shared<mt19937>(seed);
  uniform_real_distribution<> uniform;

  // compute exponential weighting scheme p[i+1] = λ*p[i], p[0] := p0; require
  // that p0 + λ*p0 + λ^2*p0 + ... + λ^(n-1)*p0 == 1.0
  const size_t n = scores.size();
  const double lambda = 0.1;
  const double p0 = (1. - lambda) / (1. - pow(lambda, n));

  // make choice proportional to total value
  const auto perm = arg_sort(scores, false);
  const double p_star = uniform(*eng);
  double p_cum = 0;
  size_t value = perm[n - 1];
  for (size_t i = 0; i < n; ++i) {
    p_cum += pow(lambda, i) * p0;
    if (p_cum > p_star) {
      value = perm[i];
      break;
    };
  }

  return value;
}

Move negamax_ab_strategy(const Slice& bk, const Slice& wt,
                         const bool blacks_turn, const Loc& capture_from,
                         const uint_fast8_t search_depth,
                         const ValueEstimator& value_estim, json* explanation) {
  printf("--- negamax/α-β, search depth %hhu, capturing from %lu, player %s\n",
         search_depth, capture_from, blacks_turn ? "black" : "white");

  const int_fast8_t color = blacks_turn ? 1 : -1;
  const int alpha = -2060606060, beta = 2060606060;  // "traceable +/- inf"

  n_evals = 0UL;

  _root_moves.clear();
  Move best_move = NO_MOVE;
  if (explanation)
    _negamax_ab_explained(bk, wt, search_depth, alpha, beta, color, best_move,
                          value_estim, *explanation);
  else
    _negamax_ab(bk, wt, search_depth, alpha, beta, color, best_move,
                value_estim, capture_from);

  printf("> evaluated %lu positions for player %s\n", n_evals,
         blacks_turn ? "black" : "white");

  const bool soft_select = false;
  if (soft_select && !_root_moves.empty()) {
    vector<int> scores;
    transform(_root_moves.begin(), _root_moves.end(), back_inserter(scores),
              [](const auto& tup) { return tup.second; });

    size_t best_ix = pick_best_ix(scores);
    best_move = _root_moves[best_ix].first;
  }

  const bool print_moves = true;
  if (print_moves) {
    printf("> move priorities, %s to pick move:\n",
           blacks_turn ? "black" : "white");
    if (!_root_moves.empty()) {
      sort(
          _root_moves.begin(), _root_moves.end(),
          [](const auto& p1, const auto& p2) { return p2.second < p1.second; });
      for (const auto& t2 : _root_moves)
        printf("  > %s: %8d%s\n", to_string(t2.first).c_str(), t2.second,
               t2.first == best_move ? " <<" : "");
    } else
      printf("  (no moves avbl)\n");
  }

  return best_move;
}

}  // namespace shashki
