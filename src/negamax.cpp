#include <limits>
#include "../include/negamax.h"
#include "../include/state.h"

int negamax(const State S) {
  return negamax(S, std::numeric_limits<int>::min(),
      std::numeric_limits<int>::max());
}

/**
 * @param S - the current state to evaluate
 * @returns if the game is winning, board_size - moves_until_win + 1.
 *   If the game is a draw, 0. If the game is losing, return
 *   moves_until_loss - board_size - 1
 */
int negamax(const State S, int lowerBoard, int upperBound) {
  if (S.isBoardFull())  // if the game is over, it's a draw
    return 0;

  int width = State::WIDTH;

  for (int x = 0; x < width; x++) {
    if (S.isPlayable(x) && S.isWinningPlay(S.getNextTileColor(), x)) {
      // If there is a winning move, return 1
      return S.getBoardSize() - S.getNumMoves();
    }
  }

  // Assume current player will lose
  int bestScore = S.getNumMoves() - S.getBoardSize();

  for (int x = 0; x < width; x++) {
    if (!S.isPlayable(x)) continue;
    State nextState = S.play(x);
    // Negative scores for our opponent are positive for us
    bestScore = std::max(bestScore, -negamax(nextState));
  }
  return bestScore;
}
