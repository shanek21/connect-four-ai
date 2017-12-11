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
int negamax(const State s, int lowerBoard, int upperBound) {
  if (s.isBoardFull())  // if the game is over, it's a draw
    return 0;

  int width = State::WIDTH;

  for (int col = 0; col < width; col++) {
    if (s.isPlayable(col) && s.isWinningPlay(s.getNextTileColor(), col)) {
      // If there is a winning move, return 1
      return S.getBoardSize() - S.getNumMoves();
    }
  }

  // Assume current player will lose
  int bestScore = S.getNumMoves() - S.getBoardSize();

  for (int col = 0; col < width; col++) {
    if (!s.isPlayable(col)) continue;
    State nextState = s.play(col);
    // Negative scores for our opponent are positive for us
    bestScore = std::max(bestScore, -negamax(nextState));
  }
  return bestScore;
}
