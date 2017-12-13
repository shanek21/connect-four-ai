#include <cassert>
#include <cstdint>
#include <iostream>
#include "../include/table.h"

Table::Table(uint32_t numBits) {
  int entryMem = sizeof(Entry);
  assert(entryMem == 8);  // should be 8 bytes
  int storedBoards = numBits / sizeof(Entry);
  table.resize(storedBoards, {0, EMPTY_VAL});  // fill vector with EMPTY_VAL
}

uint32_t Table::getTableIndex(uint64_t board) const {
  return board % table.size();
}

void Table::put(uint64_t boardKey, int8_t score) {
  assert(boardKey < (1LL << 56));
  uint32_t tableIndex = getTableIndex(boardKey);
  table[tableIndex].board = boardKey;
  table[tableIndex].score = score;
}

int8_t Table::get(uint64_t boardKey) {
  assert(boardKey < (1LL << 56));
  uint32_t tableIndex = getTableIndex(boardKey);
  if (table[tableIndex].board == boardKey) return table[tableIndex].score;
  return EMPTY_VAL;
}

