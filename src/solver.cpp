#include <limits>
#include <stdexcept>
#include <iostream>
#include "../include/solver.h"
#include "../include/state.h"
#include "../include/table.h"

Solver::Solver() : table(67108744) {  // use ~64 MB of data
  initMoveOrder(State::WIDTH);
}

void Solver::initMoveOrder(int w) {
  moveOrder = {3, 4, 2, 1, 5, 6, 0};
  /* int i = (w - 1) / 2; */
  /* int j = w / 2; */
  /* moveOrder.push_back(i); */
  /* if (i != j) moveOrder.push_back(j); */
  /* while (i > 0) { */
  /*   moveOrder.push_back(--i); */
  /*   moveOrder.push_back(++j); */
  /* } */
}

int Solver::negamax(State s) const {
  return negamax(s, -s.getBoardSize(), s.getBoardSize());
}

/**
 * @param s - the current state to evaluate
 * @param lowerBound - the lowest possible score the current player can achieve
 *   in the game
 * @param upperBound - the highest possible score the current player can achieve
 *   in the game
 * @returns if the game is winning, (board_size - moves_to_win + 2) / 2.
 *   If the game is a draw, 0. If the game is losing, return
 *   (moves_to_lose - board_size - 2) / 2. Best possible score is 21, worst
 *   is -21.
 */
int8_t Solver::negamax(State s, int8_t lowerBound, int8_t upperBound) const {
  if (s.isBoardFull()) return 0;  // if the game is over, it's a draw
  for (auto it = moveOrder.begin(); it != moveOrder.end(); it++) {
    int x = *it;
    if (s.isPlayable(x) && s.isWinningPlay(s.getNextTileColor(), x)) {
      // If there is a winning move
      return (s.getBoardSize() - s.getNumMoves() + 1) / 2;
    }
  }

  // Best case scenario, we win after our opponents next move
  int bestPossibleScore = std::max(s.getBoardSize() - s.getNumMoves() - 1, 0);
  // Can't do better than bestPossibleScore
  upperBound = std::min(upperBound, bestPossibleScore);
  if (lowerBound >= upperBound) {
    // If elsewhere we've found a higher lower bound, then assume this position
    // has the best possible score, since it will be discarded anyway
    return upperBound;
  }

  // Assume current player will lose
  int8_t bestSoFar = (s.getNumMoves() - s.getBoardSize()) / 2;

  for (auto it = moveOrder.begin(); it != moveOrder.end(); it++) {
    int x = *it;
    if (!s.isPlayable(x)) continue;
    State nextState = s.play(x);
    // Negative scores for our opponent are positive for us
    int8_t positionScore = -negamax(nextState, -upperBound, -lowerBound);
    bestSoFar = std::max(bestSoFar, positionScore);
    if (upperBound <= bestSoFar) {
      // If the upperBound is <= the current score, then this state is
      //   unreachable, so return bestSoFar (this node will be discarded)
      return bestSoFar;
    }
    // If this score is higher than the lowerBound, increase the bound
    lowerBound = std::max(lowerBound, bestSoFar);
  }
  return bestSoFar;
}
