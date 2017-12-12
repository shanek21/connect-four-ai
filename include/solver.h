#ifndef INCLUDE_SOLVER_H_
#define INCLUDE_SOLVER_H_

#include <list>
#include <cstdint>
#include "../include/state.h"
#include "../include/table.h"

class Solver {
 public:
  Solver();
  int score(State S);
 private:
  Table table;
  std::list<int> moveOrder;
  void initMoveOrder(int w);
  int8_t negamax(State S, int8_t lowerBound, int8_t upperBound);
};


#endif  // INCLUDE_SOLVER_H_
