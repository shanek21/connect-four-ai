#ifndef INCLUDE_TABLE_H_
#define INCLUDE_TABLE_H_

#include <vector>
#include <cstdint>

class Table {
 public:
  explicit Table(uint32_t numBits);
 private:
  /* struct Entry; */
  struct Entry {
    uint64_t key: 56;
    uint8_t stuff;
  };
  std::vector<Entry> T;
};

#endif  // INCLUDE_TABLE_H_
