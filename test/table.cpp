#include "../lib/catch.hpp"
#include "../include/table.h"
#include "../include/state.h"

TEST_CASE("get()") {
  Table t(8388593);
  SECTION("simple case") {
    State S = State::boardFromNums("1667675535724753771415352132");
    uint64_t key = S.boardKey();
    t.put(key, -3);
    REQUIRE(t.get(key) == -3);
    t.put(key, 40);
    REQUIRE(t.get(key) == 40);
    S = State::boardFromNums("667675535724753771415352132");
    REQUIRE(t.get(S.boardKey()) == EMPTY_VAL);
  }
}
