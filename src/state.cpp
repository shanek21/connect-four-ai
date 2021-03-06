#include <iostream>
#include <cassert>
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
  return redBoard[(row * TILEBOARD_WIDTH) + col];
}

bool State::isBlackTile(int row, int col) const {
  return blackBoard[(row * TILEBOARD_WIDTH) + col];
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

State::TileBoard State::columnMask(int col) {
  assert(col < TILEBOARD_WIDTH);
  State::TileBoard mask = 1LL << col;
  for (int i = 0; i < TILEBOARD_HEIGHT - 1; i++)
    mask |= mask << TILEBOARD_WIDTH;
  return mask;
}

State::TileBoard State::winningPositions(TileType color) const {
  int w = TILEBOARD_WIDTH;
  State::TileBoard b = color == Red ? getRedBoard() : getBlackBoard();

  State::TileBoard vertWins = (b >> w) & (b >> 2*w) & (b >> 3*w);

  State::TileBoard horzWins;
  // The right side of two horizontal pieces
  State::TileBoard rightEdge = (b << 1) & (b << 2);
  // If there is a piece either on the right of, or 3 to the left of the
  //   rightEdge, then RE is a winning play
  horzWins |= rightEdge & (b << 3);
  horzWins |= rightEdge & (b >> 1);

  State::TileBoard leftEdge = (b >> 1) & (b >> 2);
  horzWins |= leftEdge & (b >> 3);
  horzWins |= leftEdge & (b << 1);

  State::TileBoard diagWins;
  rightEdge = (b << (w - 1)) & (b << 2 * (w - 1));
  diagWins |= rightEdge & (b << 3 * (w - 1));
  diagWins |= rightEdge & (b >> 1 * (w - 1));

  rightEdge = (b >> (w - 1)) & (b >> 2 * (w - 1));
  diagWins |= rightEdge & (b >> 3 * (w - 1));
  diagWins |= rightEdge & (b << 1 * (w - 1));

  rightEdge = (b << (w + 1)) & (b << 2 * (w + 1));
  diagWins |= rightEdge & (b << 3 * (w + 1));
  diagWins |= rightEdge & (b >> 1 * (w + 1));

  rightEdge = (b >> (w + 1)) & (b >> 2 * (w + 1));
  diagWins |= rightEdge & (b >> 3 * (w + 1));
  diagWins |= rightEdge & (b << 1 * (w + 1));


  State::TileBoard dummyColumn = columnMask(WIDTH);
  State::TileBoard allWins = vertWins | horzWins | diagWins;
  State::TileBoard alreadyPlayed = getRedBoard() | getBlackBoard();
  State::TileBoard cantWin = alreadyPlayed | dummyColumn;
  return allWins & ~cantWin;
}

bool State::hasTile(TileBoard board, int row, int col) {
  return board[(row * TILEBOARD_WIDTH) + col];
}

uint64_t State::boardKey() const {
  // TODO(davidabrahams): I'm not entirely sure how this makes each potential
  //   gamestate have a unique key
  uint64_t currPlayerBoard = (getNextTileColor() ==
      Red ? getRedBoard() : getBlackBoard()).to_ulong();
  uint64_t nextPlayerBoard = (getNextTileColor() ==
      Black ? getRedBoard() : getBlackBoard()).to_ulong();
  uint64_t key = currPlayerBoard + (currPlayerBoard | nextPlayerBoard);
  return key;
}

State::TileBoard State::getNextToMoveBoard() const {
  return getNextTileColor() == Red ? getRedBoard() : getBlackBoard();
}

State::TileType State::getNextTileColor() const {
  return (numMoves % 2 == 0) ? Red : Black;
}

State State::play(int col) const {
  return play(getNextTileColor(), col);
}

State State::play(State::TileType color, int col) const {
  // TODO(davidabrahams): do this with bitshifting
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
  TileBoard tb = (color == Red) ? s.getRedBoard() : s.getBlackBoard();
  TileBoard temp;

  // Check -
  temp = tb & (tb >> 1);
  temp = temp & (temp >> 2);
  if (temp.any()) return true;

  // Check |
  temp = tb & (tb >> TILEBOARD_WIDTH);
  temp = temp & (temp >> 2 * TILEBOARD_WIDTH);
  if (temp.any()) return true;

  // Check /
  temp = tb & (tb >> (TILEBOARD_WIDTH - 1));
  temp = temp & (temp >> 2 * (TILEBOARD_WIDTH - 1));
  if (temp.any()) return true;

  // Check top-left to bot-right diagonal
  temp = tb & (tb >> (TILEBOARD_WIDTH + 1));
  temp = temp & (temp >> 2 * (TILEBOARD_WIDTH + 1));
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

void State::placeTile(State::TileType color, int row, int col) {
  if (color == Empty)
    throw std::runtime_error("Tried to place an empty tile");

  if (!isEmpty(row, col))
    throw std::runtime_error("Tried to overwrite an existing tile");


  if (color == Red)
    redBoard[(row * TILEBOARD_WIDTH) + col] = 1;
  else
    blackBoard[(row * TILEBOARD_WIDTH) + col] = 1;
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
