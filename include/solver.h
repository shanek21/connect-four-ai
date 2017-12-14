#ifndef INCLUDE_SOLVER_H_
#define INCLUDE_SOLVER_H_

#include <list>
#include <vector>
#include <cstdint>
#include <utility>
#include "../include/state.h"
#include "../include/table.h"

class Solver {
 public:
  Solver();
  int score(State s);
  int bestMove(State s);
  std::vector<int> heuristicMoveOrder(State s) const;
  std::pair<int, int> bestMoveAndScore(State S);
 private:
  Table table;
  std::list<int> moveOrder;
  void initMoveOrder(int w);
  std::pair<int, int> negamax(State S, int8_t lowerBound, int8_t upperBound);
};


#endif  // INCLUDE_SOLVER_H_
