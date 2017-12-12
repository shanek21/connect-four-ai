#ifndef INCLUDE_BIT_BOARD_H_
#define INCLUDE_BIT_BOARD_H_


#include <bitset>
#include <string>
#include <iostream>

#include "./utils.h"


class BitBoard {
 public:
  BitBoard();

  template <size_t size>
  explicit BitBoard(std::bitset<size> b);

  void initializeMasks();

  bool get(int row, int col) const;

  BitBoard shift(int n) const;

  BitBoard circularShift(int n) const;

  void set(int minRow, int maxRow, int minCol, int maxCol);

  void set(int row, int col);

  BitBoard operator&(const BitBoard* other) const;

  BitBoard operator|(const BitBoard& other) const;

 private:
  BitBoard* LEFT_MASK;
  BitBoard* RIGHT_MASK;
  static bool masksInitialized = false;

  std::bitset<(WIDTH + 1) * HEIGHT> bits;
};


#endif   // INCLUDE_BIT_BOARD_H_
