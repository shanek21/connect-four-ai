#include <limits>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <algorithm>
#include "../include/solver.h"

// Use ~64 MB of data, since each board is 8 bytes
Solver::Solver() : table(8388593) {
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

std::vector<int> Solver::heuristicMoveOrder(State s) const {
  std::vector<int> winningMovesCreated(State::WIDTH);
  // Copy moveOrder to order
  std::vector<int> order(moveOrder.size());
  int i = 0;
  for (auto it = moveOrder.begin(); it != moveOrder.end(); it++) {
    int j = *it;
    order[i] = j;
    i++;
  }
  // Calculate our heuristic for each move in order
  for (auto it = order.begin(); it != order.end(); it++) {
    int i = *it;
    if (!s.isPlayable(i)) {
      continue;
    }
    winningMovesCreated[i] = s.play(i).winningPositions(
          s.getNextTileColor()).count();
  }
  // Sort the heuristic order based on the amount of winning moves created
  std::sort(order.begin(), order.end(),
      [&winningMovesCreated](const int a, const int b) -> bool {
      return winningMovesCreated[a] > winningMovesCreated[b];
    });
  return order;
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
std::pair<int, int> Solver::negamax(State s, int8_t lowerBound,
    int8_t upperBound) {
  std::pair<int, int> result;
  result.first = -1;
  result.second = 0;
  int8_t score;
  if (s.isBoardFull()) return result;  // if the game is over, it's a draw
  for (auto it = moveOrder.begin(); it != moveOrder.end(); it++) {
    int x = *it;
    if (s.isPlayable(x) && s.isWinningPlay(s.getNextTileColor(), x)) {
      // If there is a winning move
      score = (s.getBoardSize() - s.getNumMoves() + 1) / 2;
      result.first = x;
      result.second = score;
      return result;
    }
  }

  // Best case scenario, we win after our opponents next move
  int8_t bestPossibleScore = (s.getBoardSize() - s.getNumMoves() - 1) / 2;
  int8_t tableVal = table.get(s.boardKey());

  assert(bestPossibleScore >= 0);

  // If there's already an upper bound stored in the table, it is the best
  //   possible score
  if (tableVal != EMPTY_VAL) {
    bestPossibleScore = tableVal;
  }

  // Can't do better than bestPossibleScore
  upperBound = std::min(upperBound, bestPossibleScore);
  if (lowerBound >= upperBound) {
    // If elsewhere we've found a higher lower bound, then assume this position
    // has the best possible score, since it will be discarded anyway
    score = upperBound;
    result.second = score;
    return result;
  }

  // Assume current player will lose
  int8_t bestSoFar = (s.getNumMoves() - s.getBoardSize()) / 2;

  std::vector<int> heurOrder = heuristicMoveOrder(s);
  for (auto it = heurOrder.begin(); it != heurOrder.end(); it++) {
  /* for (auto it = moveOrder.begin(); it != moveOrder.end(); it++) { */
    int x = *it;
    if (!s.isPlayable(x)) continue;
    State nextState = s.play(x);
    // Negative scores for our opponent are positive for us
    int8_t positionScore = -negamax(nextState, -upperBound, -lowerBound).second;
    bestSoFar = std::max(bestSoFar, positionScore);
    if (upperBound <= bestSoFar) {
      // If the upperBound is <= the current score, then this state is
      //   unreachable, so return bestSoFar (this node will be discarded)
      score = bestSoFar;
      result.second = score;
      return result;
    }
    if (bestSoFar > lowerBound) {
      result.first = x;
    }
    // If this score is higher than the lowerBound, increase the bound
    lowerBound = std::max(lowerBound, bestSoFar);
  }
  score = bestSoFar;
  table.put(s.boardKey(), score);
  result.second = score;
  return result;
  /* return score; */
}

std::pair<int, int> Solver::bestMoveAndScore(State S) {
  table.reset();
  int min = -S.getBoardSize() / 2;
  int max = S.getBoardSize() / 2;
  std::pair<int, int> nm;
  // run a binary search
  while (min < max) {
    int med = min + (max - min) / 2;
    nm = negamax(S, med, med + 1);
    if (nm.second <= med)
      max = nm.second;
    else
      min = nm.second;
  }
  return nm;
}

int Solver::score(State s) {
  return bestMoveAndScore(s).second;
}

int Solver::bestMove(State s) {
  return bestMoveAndScore(s).first;
}

