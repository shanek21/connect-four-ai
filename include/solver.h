#ifndef INCLUDE_SOLVER_H_
#define INCLUDE_SOLVER_H_

#include <list>
#include "../include/state.h"
#include "../include/table.h"

class Solver {
 public:
  Solver();
  int negamax(State S) const;
  int negamax(State S, int lowerBound, int upperBound) const;
 private:
  Table table;
  std::list<int> moveOrder;
  void initMoveOrder(int w);
};


#endif  // INCLUDE_SOLVER_H_
