#include <cassert>
#include <cstdint>
#include <iostream>
#include "../include/table.h"

Table::Table(uint32_t numBits) {
  int entryMem = sizeof(Entry);
  // TODO(davidabrahams) remove this
  assert(entryMem == 8);  // should be 8 bytes
  int storedBoards = numBits / sizeof(Entry);
  std::cout << storedBoards << std::endl;
  table.resize(storedBoards, {0, 0});  // fill vector with all-0 structs
}

uint32_t Table::getTableIndex(uint64_t board) const {
  return board % table.size();
}

void Table::put(State::TileBoard board, uint8_t score) {
  uint64_t boardInt = board.to_ulong();
  uint32_t tableIndex = getTableIndex(boardInt);
  table[tableIndex].board = boardInt;
  table[tableIndex].score = score;
}

