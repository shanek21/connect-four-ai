#include "../lib/catch.hpp"
#include "../include/state.h"
#include "../include/negamax.h"

TEST_CASE("negamax()") {
  SECTION("Losing") {
    State S = State::boardFromNums("2252576253462244111563365343671351441");
    REQUIRE(negamax(S) < 0);
    S = State::boardFromNums("3575316255751336464276636772271112");
    REQUIRE(negamax(S) < 0);
  }
  SECTION("Winning") {
    State S = State::boardFromNums("7422341735647741166133573473242566");
    REQUIRE(negamax(S) > 0);
    S = State::boardFromNums("326615663752621323655335514271");
    REQUIRE(negamax(S) > 0);
    /* S = State::boardFromNums(""); */
    /* REQUIRE(negamax(S) == 1); */
  }
  SECTION("Draw") {
    State S = State::boardFromNums("23163416124767223154467471272416755633");
    REQUIRE(negamax(S) == 0);
    S = State::boardFromNums("7172212567451542223676134464437761515");
    REQUIRE(negamax(S) == 0);
  }
}
