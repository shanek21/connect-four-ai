#include <cassert>
#include <cstdint>
#include <iostream>
#include "../include/table.h"

Table::Table(uint32_t numBits) {
  int entryMem = sizeof(Entry);
  std::cout << entryMem << std::endl;
  // TODO(davidabrahams) remove this
  assert(entryMem == 8);  // should be 8 bytes
  int storedBoards = numBits / sizeof(Entry);
  T.reserve(storedBoards);
}
