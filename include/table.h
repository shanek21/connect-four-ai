#ifndef INCLUDE_TABLE_H_
#define INCLUDE_TABLE_H_

#include <vector>
#include <cstdint>

#include "./state.h"

class Table {
 public:
  explicit Table(uint32_t numBits);
  void put(State::TileBoard board, uint8_t score);
 private:
  uint32_t getTableIndex(uint64_t board) const;
  struct Entry {
    uint64_t board: 56;
    int8_t score;
  };
  std::vector<Entry> table;
};

#endif  // INCLUDE_TABLE_H_
