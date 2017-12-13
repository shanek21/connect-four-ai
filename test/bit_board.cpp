#include "../lib/catch.hpp"
#include "../include/bit_board.h"


TEST_CASE("set() and get()") {
  BitBoard bb;

  SECTION("simple") {
    bb.set(0, 0);
    REQUIRE(bb.get(0, 0) == 1);
    bb.set(2, 5);
    REQUIRE(bb.get(2, 5) == 1);
    REQUIRE(bb.get(2, 2) == 0);
  }

  SECTION("complex") {
    int minRow = 4;
    int maxRow = 6;
    int minCol = 1;
    int maxCol = 4;
    bb.set(minRow, maxRow, minCol, maxCol);
    for (int row = minRow; row < maxRow; row++) {
      for (int col = minCol; col < maxCol; col++) {
        REQUIRE(bb.get(row, col) == 1);
      }
    }
  }
}

TEST_CASE("shift()") {
  BitBoard bb;
  bb.set(0, 0);
  bb = bb.shift(1);
  REQUIRE(bb.get(0, 1) == 1);
  bb.set(1, 1);
  bb = bb.shift(-1);
  REQUIRE(bb.get(1, 0) == 1);
}

TEST_CASE("circularShift()") {
  BitBoard bb;
  bb.set(3, 0);
  bb = bb.circularShift(1);
  REQUIRE(bb.get(3, 1) == 1);

  bb.set(4, 0);
  bb = bb.circularShift(WIDTH);
  REQUIRE(bb.get(4, 0) == 1);

  bb.set(1, 6);
  bb = bb.circularShift(3);
  REQUIRE(bb.get(1, 2) == 1);

  bb.set(0, 0);
  bb.set(0, 1);
  bb.set(0, 2);
  bb.set(0, 4);
  bb = bb.circularShift(-2);
  REQUIRE(bb.get(0, 0) == 1);
  REQUIRE(bb.get(0, 1) == 0);
  REQUIRE(bb.get(0, 2) == 1);
  REQUIRE(bb.get(0, 3) == 0);
  REQUIRE(bb.get(0, 4) == 0);
  REQUIRE(bb.get(0, 5) == 1);
  REQUIRE(bb.get(0, 6) == 1);
}
