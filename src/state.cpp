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
  return getRedBoard().get(row, col);
}

bool State::isBlackTile(int row, int col) const {
  return getBlackBoard().get(row, col);
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

BitBoard State::getRedBoard() const {
  return redBoard;
}

BitBoard State::getBlackBoard() const {
  return blackBoard;
}

State::TileType State::getNextTileColor() const {
  return (numMoves % 2 == 0) ? Red : Black;
}

State State::play(int col) const {
  return play(getNextTileColor(), col);
}

State State::play(State::TileType color, int col) const {
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

bool State::isWinningPlay(State::TileType color, int col) const {
  State s = play(color, col);
  BitBoard bb = (color == Red) ? s.getRedBoard() : s.getBlackBoard();
  BitBoard temp;

  // Check -
  temp = bb & (bb >> 1);
  temp = temp & (temp >> 2);
  if (temp.any()) return true;

  // Check |
  temp = bb & (bb >> (WIDTH + 1));
  temp = temp & (temp >> 2 * (WIDTH + 1));
  if (temp.any()) return true;

  // Check /
  temp = bb & (bb >> WIDTH);
  temp = temp & (temp >> 2 * WIDTH);
  if (temp.any()) return true;

  // Check top-left to bot-right diagonal
  temp = bb & (bb >> (WIDTH + 2));
  temp = temp & (temp >> 2 * (WIDTH + 2));
  if (temp.any()) return true;

  return false;
}

int State::getNumMoves() const {
  return numMoves;
}


int State::getBoardSize() const {
  return WIDTH * HEIGHT;
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
  assert(color != Empty);
  assert(isEmpty(row, col));

  if (color == Red) {
    redBoard.set(row, col);
  } else {
    blackBoard.set(row, col);
  }
}

std::ostream& operator<<(std::ostream& os, const State::TileType& t) {
  if (t == State::Red) return os << "R";
  if (t == State::Black) return os << "B";
  return os << "E";
}

State State::boardFromNums(std::string nums) {
  State S;
  for (std::string::iterator it = nums.begin(); it != nums.end(); ++it) {
    char n = *it;
    // Convert the char to a number and 0-index it
    S = S.play(S.getNextTileColor(), n - '1');
  }
  return S;
}
