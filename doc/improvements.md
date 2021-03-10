# Incremental Improvements

## 1) Value Function
The current version of the value function is heavily based on simple heuristics such as
the golden checker, key positions and some counting scheme. While this is a good
starting point and manual improvements still seem possible, a more interesting approach
will be to use some kind of learned value function. Suitable methods may be borrowed
from RL such as
[TD-learning](https://en.wikipedia.org/wiki/Temporal_difference_learning) (as used in
[Q-learing](https://en.wikipedia.org/wiki/Q-learning)), or machine learning in general.

Another idea may involve using robust global optimizers such as
[CMA-ES](http://cma.gforge.inria.fr/) in order to evolve a suitable value function.
Initial experiments in this direction revealed some potential but got abandoned due to
time constraints. Code for this is in `experimental/cmaes_for_value_func/` and can
should seamlessly integrate with the rest of the code.

## 2) General Gameplay
* Fix known issue(s)
* Remove bias in move selection by random-uniformly sampling multiple moves sharing the
  same top value
* The current front-end always requires to play white, however the backend supports both
  colors equally
* Lack of an [end-game tablebase](https://en.wikipedia.org/wiki/Endgame_tablebase)
* Introduce [transposition tables](https://en.wikipedia.org/wiki/Transposition_table) to
  avoid evaluating the same positiion more than once and enabling deeper searches

## 3) Move Time Control
Introduce move time control through [iterative deepening
DFS](https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search) or similar
techniques

## 4) [Checkerboard](http://www.fierz.ch/checkerboard.php) Integration
This will allow the engine to play against other engines (Windows only, possibly working
with Mono too)

## 5) Performance
* Enable parallel evaluation of the game tree (non-trivial due to pruning)
* Use SIMD intrinsics (AVX2) for low-level parallel evaluations. The latter should be
  particularly effective in computing feasible moves as done in
  `src/generated/valid_moves.cc`
* Reduce/remove dynamic heap allocations, i.e. look for `std::vector`) and use
  fixed-size arrays instead
* Tune compilation
  * Profile-guided optimization: first `-fprofile-generate`, then `-fprofile-use`
  * Minor impact: `-fopenmp` `-D_GLIBCXX_PARALLEL` `-frename-registers`
  * Squeezing-out the very last cycles: `https://cutt.ly/ZjmJZeG`

## 6) Advanced Search Algorithm
Complement/replace negamax with either of [MTD-f](https://en.wikipedia.org/wiki/MTD-f),
[SSS*](https://en.wikipedia.org/wiki/SSS*),
[A*](https://en.wikipedia.org/wiki/A*_search_algorithm)

## 7) Application Design
* Move test code into proper framework such as CTest or
  [GoogleTest](https://github.com/google/googletest)
* Add tests for REST API

## 8) Docs
* Add build instructions on Windows/OSX
* Document the REST API with an IDL such as [Swagger](https://swagger.io/)
