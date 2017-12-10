#include "../include/negamax.h"
#include "../include/state.h"

/**
 * @param S - the current state to evaluate
 * @returns 1 if the next player to play can win, 0 if the game is a draw, -1
 *   if the next player to play will lose
 */
int negamax(const State S) {
  if (S.isBoardFull())  // if the game is over, it's a draw
    return 0;

  int width = State::WIDTH;

  for (int x = 0; x < width; x++) {
    if (S.isPlayable(x) && S.isWinningPlay(S.getNextTileColor(), x)) {
      // If there is a winning move, return 1
      return 1;
    }
  }

  // Assume current player will lose
  int bestScore = -1;

  for (int x = 0; x < width; x++) {
    if (!S.isPlayable(x)) continue;
    State nextState = S.play(x);
    // Negative scores for our opponent are positive for us
    bestScore = std::max(bestScore, -negamax(nextState));
    if (bestScore == 1) return 1;  // if we've found a winning move, return
  }
  return bestScore;
}
