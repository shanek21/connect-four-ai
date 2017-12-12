#include "../lib/catch.hpp"
#include "../include/state.h"
#include "../include/solver.h"

TEST_CASE("negamax()") {
  Solver solver;
  SECTION("Losing") {
    State S = State::boardFromNums("2252576253462244111563365343671351441");
    REQUIRE(solver.score(S) < 0);
    S = State::boardFromNums("3575316255751336464276636772271112");
    REQUIRE(solver.score(S) < 0);
    S = State::boardFromNums("12514726155174536522772517671");
    REQUIRE(solver.score(S) < 0);
    S = State::boardFromNums("43745416472735");
    REQUIRE(solver.score(S) == -13);
  }

  SECTION("Winning") {
    State S = State::boardFromNums("7422341735647741166133573473242566");
    REQUIRE(solver.score(S) > 0);
    S = State::boardFromNums("326615663752621323655335514271");
    REQUIRE(solver.score(S) > 0);
    S = State::boardFromNums("24617524315172127");
    REQUIRE(solver.score(S) > 0);
    // This takes about 4 seconds
    /* S = State::boardFromNums("7234472553"); */
    /* REQUIRE(solver.score(S) == 10); */
    // This is unsolvable (for now)
    /* S = State::boardFromNums("266674777"); */
    /* REQUIRE(solver.score(S) == 4); */
  }
  SECTION("Draw") {
    State S = State::boardFromNums("74425337641465475671176741236615215533");
    REQUIRE(solver.score(S) == 0);
    S = State::boardFromNums("34441157374153736716346556774311552222");
    REQUIRE(solver.score(S) == 0);
    S = State::boardFromNums("23163416124767223154467471272416755633");
    REQUIRE(solver.score(S) == 0);
    S = State::boardFromNums("7172212567451542223676134464437761515");
    REQUIRE(solver.score(S) == 0);
  }
}
