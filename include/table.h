#ifndef INCLUDE_TABLE_H_
#define INCLUDE_TABLE_H_

#include <vector>
#include <limits>
#include <cstdint>

const int8_t EMPTY_VAL = std::numeric_limits<int8_t>::min();

class Table {
 public:
  explicit Table(uint32_t numBits);
  void put(uint64_t boardKey, int8_t score);
  void reset();
  int8_t get(uint64_t boardKey);

 private:
  uint32_t getTableIndex(uint64_t board) const;
  struct Entry {
    uint64_t board: 56;
    int8_t score;
  };
  std::vector<Entry> table;
};

#endif  // INCLUDE_TABLE_H_
