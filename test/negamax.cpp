#include "../lib/catch.hpp"
#include "../include/state.h"
#include "../include/negamax.h"

TEST_CASE("negamax()") {
  State S = State::boardFromNums("2252576253462244111563365343671351441");
  REQUIRE(negamax(S) == -1);
}
