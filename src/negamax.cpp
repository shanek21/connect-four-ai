#include <limits>
#include <stdexcept>
#include <iostream>
#include "../include/negamax.h"
#include "../include/state.h"

Solver::Solver() {
  int w = State::WIDTH;
  int i = (w - 1) / 2;
  int j = w / 2;
  moveOrder.push_back(i);
  if (i != j) moveOrder.push_back(j);
  while (i > 0) {
    moveOrder.push_back(--i);
    moveOrder.push_back(++j);
  }
}

int Solver::negamax(State S) {
  return negamax(S, -S.getBoardSize(), S.getBoardSize());
}

/**
 * @param S - the current state to evaluate
 * @returns if the game is winning, board_size - moves_until_win + 1.
 *   If the game is a draw, 0. If the game is losing, return
 *   moves_until_loss - board_size - 1
 */
int Solver::negamax(State S, int lowerBound, int upperBound) {
  if (S.isBoardFull()) {  // if the game is over, it's a draw
    return 0;
  }

  for (auto it = moveOrder.begin(); it != moveOrder.end(); it++) {
    int x = *it;
    if (S.isPlayable(x) && S.isWinningPlay(S.getNextTileColor(), x)) {
      // If there is a winning move
      return S.getBoardSize() - S.getNumMoves();
    }
  }

  // Best case scenario, we win after our opponents next move
  int bestPossibleScore = std::max(S.getBoardSize() - S.getNumMoves() - 2, 0);
  // Can't do better than bestPossibleScore
  upperBound = std::min(upperBound, bestPossibleScore);
  if (lowerBound >= upperBound) {
    // If elsewhere we've found a higher lower bound, then assume this position
    // has the best possible score, since it will be discarded anyway
    return upperBound;
  }

  // Assume current player will lose
  int bestSoFar = S.getNumMoves() - S.getBoardSize();

  for (auto it = moveOrder.begin(); it != moveOrder.end(); it++) {
    int x = *it;
    if (!S.isPlayable(x)) continue;
    State nextState = S.play(x);
    // Negative scores for our opponent are positive for us
    bestSoFar = std::max(bestSoFar,
        -negamax(nextState, -upperBound, -lowerBound));
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
