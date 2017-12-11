#include <limits>
#include <stdexcept>
#include <iostream>
#include "../include/negamax.h"
#include "../include/state.h"

int negamax(const State S) {
  return negamax(S, -S.getBoardSize(), S.getBoardSize());
}

/**
 * @param S - the current state to evaluate
 * @returns if the game is winning, board_size - moves_until_win + 1.
 *   If the game is a draw, 0. If the game is losing, return
 *   moves_until_loss - board_size - 1
 */
int negamax(const State S, int lowerBound, int upperBound) {
  if (S.isBoardFull()) {  // if the game is over, it's a draw
    return 0;
  }

  int width = State::WIDTH;

  for (int x = 0; x < width; x++) {
    if (S.isPlayable(x) && S.isWinningPlay(S.getNextTileColor(), x)) {
      // If there is a winning move
      return S.getBoardSize() - S.getNumMoves();
    }
  }

  // Best case scenario, we win after our opponents next move
  int bestPossibleScore = std::max(S.getBoardSize() - S.getNumMoves() - 2, 0);
  // Can't do better than bestPossibleScore
  upperBound = std::min(upperBound, bestPossibleScore);
  // If elsewhere we've found a higher lower bound, then assume this position
  // has the best possible score, since it will be discarded anyway
  if (lowerBound >= upperBound) {
    return upperBound;
  }

  // Assume current player will lose
  int bestScore = S.getNumMoves() - S.getBoardSize();

  for (int x = 0; x < width; x++) {
    if (!S.isPlayable(x)) continue;
    State nextState = S.play(x);
    // Negative scores for our opponent are positive for us
    bestScore = std::max(bestScore,
        -negamax(nextState, -upperBound, -lowerBound));
    // If this score is higher than the lowerBound, increase the bound
    lowerBound = std::max(lowerBound, bestScore);
    if (upperBound <= lowerBound) {
      // If the upperBound is <= the current lower bound, then this state is
      //   unreachable, so return bestScore (this node will be discarded)
      return bestScore;
    }
  }
  return bestScore;
}
