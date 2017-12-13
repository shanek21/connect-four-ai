#include "../include/bit_board.h"


BitBoard::BitBoard() {}

template <size_t size>
BitBoard::BitBoard(std::bitset<size> b) : bits(b) {}

bool BitBoard::get(int row, int col) const {
  return bits[(row * (WIDTH + 1)) + col];
}

bool BitBoard::any() const {
  return bits.any();
}

BitBoard BitBoard::shift(int offset) const {
  if (offset > 0) return BitBoard(bits << offset);
  return BitBoard(bits >> abs(offset));
}

BitBoard BitBoard::circularShift(int offset) const {
  offset %= WIDTH;
  BitBoard LEFT_MASK;
  BitBoard RIGHT_MASK;

  if (offset > 0) {
    LEFT_MASK.set(0, HEIGHT, 0, offset);
    RIGHT_MASK.set(0, HEIGHT, offset, WIDTH);
    return (shift(offset) & RIGHT_MASK) |
      (shift(-WIDTH + offset) & LEFT_MASK);
  } else {
    LEFT_MASK.set(0, HEIGHT, 0, WIDTH + offset);
    RIGHT_MASK.set(0, HEIGHT, WIDTH + offset, WIDTH);
    return (shift(offset) & LEFT_MASK) |
      (shift(WIDTH + offset) & RIGHT_MASK);
  }
}

void BitBoard::set(int minRow, int maxRow, int minCol, int maxCol) {
  for (int row = minRow; row < maxRow; row++) {
    for (int col = minCol; col < maxCol; col++) {
      set(row, col);
    }
  }
}

void BitBoard::set(int row, int col) {
  bits.set((row * (WIDTH + 1)) + col);
}

BitBoard BitBoard::operator&(const BitBoard& other) const {
  return BitBoard(bits & other.bits);
}

BitBoard BitBoard::operator|(const BitBoard& other) const {
  return BitBoard(bits | other.bits);
}

BitBoard BitBoard::operator>>(int offset) const {
  return BitBoard(bits >> offset);
}

BitBoard BitBoard::operator<<(int offset) const {
  return BitBoard(bits << offset);
}

std::ostream& operator<<(std::ostream& os, const BitBoard& bb) {
  return os << bb.bits;
}
