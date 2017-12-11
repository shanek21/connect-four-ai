#include <iostream>
#include <stdexcept>

#include "../include/state.h"


State::State() {
  numMoves = 0;
}

State::State(const State* s) {
  redBoard = s->getRedBoard();
  blackBoard = s->getBlackBoard();
  numMoves = s->getNumMoves();
}

bool State::isRedTile(int row, int col) const {
  return redBoard[(row * WIDTH) + col];
}

bool State::isBlackTile(int row, int col) const {
  return blackBoard[(row * WIDTH) + col];
}

State::TileType State::getTile(int row, int col) const {
  if (isRedTile(row, col)) return Red;
  if (isBlackTile(row, col)) return Black;
  return Empty;
}

bool State::isEmpty(int row, int col) const {
  if (getTile(row, col) == Empty) return true;
  return false;
}

State::TileBoard State::getRedBoard() const {
  return redBoard;
}

State::TileBoard State::getBlackBoard() const {
  return blackBoard;
}

State State::play(TileType color, int col) const {
  State stateAfterPlay = State(this);
  for (int row = HEIGHT - 1; row >= 0; row--) {
    if (isEmpty(row, col)) {
      stateAfterPlay.placeTile(color, row, col);
      stateAfterPlay.incrementNumMoves();
      return stateAfterPlay;
    }
  }
  throw std::exception();
}

bool State::isPlayable(int col) const {
  if (getTile(0, col) == Empty) return true;
  return false;
}

bool State::isWinningPlay(TileType color, int col) const {
  State s = play(color, col);
  TileBoard tb = (color == Red) ? s.getRedBoard() : s.getBlackBoard();
  TileBoard temp;

  // Check -
  temp = tb & (tb >> 1);
  temp = temp & (temp >> 2);
  if (temp.any()) return true;

  // Check |
  temp = tb & (tb >> WIDTH);
  temp = temp & (tb >> 2 * WIDTH);
  if (temp.any()) return true;

  // Check /
  temp = tb >> (WIDTH - 1);
  temp = temp & (temp >> 2 * (WIDTH - 1));
  if (temp.any()) return true;

  // Check top-left to bot-right diagonal
  temp = tb >> (WIDTH + 1);
  temp = temp & (tb >> 2 * (WIDTH + 1));
  if (temp.any()) return true;

  return false;
}

int State::getNumMoves() const {
  return numMoves;
}

void State::incrementNumMoves() {
  if (numMoves >= WIDTH * HEIGHT) {
    throw std::runtime_error("Tried to over increment numMoves");
  }
  numMoves++;
}

bool State::isBoardFull() const {
  if (getNumMoves() == WIDTH * HEIGHT) return true;
  return false;
}

void State::placeTile(TileType color, int row, int col) {
  if (color == Empty) {
    throw std::runtime_error("Tried to place an empty tile");
  }
  if (!isEmpty(row, col)) {
    throw std::runtime_error("Tried to overwrite an existing tile");
  }

  if (color == Red) {
    redBoard[(row * WIDTH) + col] = 1;
  } else if (color == Black) {
    blackBoard[(row * WIDTH) + col] = 1;
  } else {
  }
}

std::ostream& operator<<(std::ostream& os, const State::TileType& t) {
  if (t == State::Red) return os << "R";
  if (t == State::Black) return os << "B";
  return os << "E";
}
