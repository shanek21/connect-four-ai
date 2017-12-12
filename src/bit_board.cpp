#include "../include/bit_board.h"


BitBoard::BitBoard() {
  std::cout << "starting" << std::endl;
  if (!masksInitialized) {
    std::cout << "init masks" << std::endl;
    masksInitialized = true;
  }
}

template <size_t size>
BitBoard::BitBoard(std::bitset<size> b) : bits(b) {}

void BitBoard::initializeMasks() {
  LEFT_MASK = new BitBoard();
  LEFT_MASK->set(0, HEIGHT, 0, WIDTH / 2);
  RIGHT_MASK = new BitBoard();
  RIGHT_MASK->set(0, HEIGHT, WIDTH / 2, WIDTH);
}

bool BitBoard::get(int row, int col) const {
  return bits[(row * WIDTH + 1) + col];
}

BitBoard BitBoard::shift(int shift) const {
  return BitBoard();
}

BitBoard BitBoard::circularShift(int offset) const {
  offset %= WIDTH;
  if (offset > 0) {
    return (shift(offset) & RIGHT_MASK) | (shift(WIDTH - offset) & LEFT_MASK);
  }
  return shift(offset) | shift(WIDTH - offset);
}

void BitBoard::set(int minRow, int maxRow, int minCol, int maxCol) {
  for (int row = minRow; row < maxRow; row++) {
    for (int col = minCol; col < maxCol; col++) {
      set(row, col);
    }
  }
}

void BitBoard::set(int row, int col) {
  bits.set((row * WIDTH) + col);
}

BitBoard BitBoard::operator&(const BitBoard* other) const {
  return BitBoard(bits & other->bits);
}

BitBoard BitBoard::operator|(const BitBoard& other) const {
  return BitBoard(bits | other.bits);
}
