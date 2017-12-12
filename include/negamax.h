#ifndef INCLUDE_NEGAMAX_H_
#define INCLUDE_NEGAMAX_H_

#include <list>
#include "../include/state.h"

class Solver {
 public:
  Solver();
  int negamax(State S);
  int negamax(State S, int lowerBound, int upperBound);
 protected:
  std::list<int> moveOrder;
};


#endif  // INCLUDE_NEGAMAX_H_
