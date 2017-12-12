#include "../include/negamax.h"
#include "../include/state.h"

/**
 * @param S - the current state to evaluate
 * @returns 1 if the next player to play can win, 0 if the game is a draw, -1
 *   if the next player to play will lose
 */
int negamax(const State s) {
  if (s.isBoardFull()) return 0;  // if the game is over, it's a draw

  int width = State::WIDTH;

  for (int col = 0; col < width; col++) {
    if (s.isPlayable(col) && s.isWinningPlay(s.getNextTileColor(), col)) {
      // If there is a winning move, return 1
      return 1;
    }
  }

  // Assume current player will lose
  int bestScore = -1;

  for (int col = 0; col < width; col++) {
    if (!s.isPlayable(col)) continue;
    State nextState = s.play(col);
    // Negative scores for our opponent are positive for us
    bestScore = std::max(bestScore, -negamax(nextState));
    if (bestScore == 1) return 1;  // if we've found a winning move, return
  }
  return bestScore;
}
