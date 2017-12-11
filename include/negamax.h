#ifndef INCLUDE_NEGAMAX_H_
#define INCLUDE_NEGAMAX_H_

#include "../include/state.h"

int negamax(const State S);
int negamax(const State S, int lowerBoard, int upperBound);

#endif  // INCLUDE_NEGAMAX_H_
