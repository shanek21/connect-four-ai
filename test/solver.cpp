#include "../lib/catch.hpp"
#include "../include/state.h"
#include "../include/solver.h"

TEST_CASE("negamax broken", "[!mayfail]") {
  Solver solver;
  SECTION("Broken0") {
    State S = State::boardFromNums("1667675535724753771415352132");
    REQUIRE(solver.score(S) == 1);
  }
  SECTION("Broken1") {
    State S = State::boardFromNums("427631264721");
    REQUIRE(solver.score(S) == 10);
  }
  SECTION("Broken2") {
    State S = State::boardFromNums("11163142533736577");
    REQUIRE(solver.score(S) == 2);
  }
}

TEST_CASE("negamax()") {
  Solver solver;
  SECTION("Losing") {
    State S = State::boardFromNums("2252576253462244111563365343671351441");
    REQUIRE(solver.negamax(S) < 0);
    S = State::boardFromNums("3575316255751336464276636772271112");
    REQUIRE(solver.negamax(S) < 0);
    S = State::boardFromNums("12514726155174536522772517671");
    REQUIRE(solver.negamax(S) < 0);
  }
  SECTION("Winning") {
    State S = State::boardFromNums("7422341735647741166133573473242566");
    REQUIRE(solver.negamax(S) > 0);
    S = State::boardFromNums("326615663752621323655335514271");
    REQUIRE(solver.negamax(S) > 0);
    S = State::boardFromNums("24617524315172127");
    REQUIRE(solver.negamax(S) > 0);
  }
  SECTION("Draw") {
    State S = State::boardFromNums("74425337641465475671176741236615215533");
    REQUIRE(solver.negamax(S) == 0);
    S = State::boardFromNums("34441157374153736716346556774311552222");
    REQUIRE(solver.negamax(S) == 0);
    S = State::boardFromNums("23163416124767223154467471272416755633");
    REQUIRE(solver.negamax(S) == 0);
    S = State::boardFromNums("7172212567451542223676134464437761515");
    REQUIRE(solver.negamax(S) == 0);
  }
  SECTION("Test1") {
    State S = State::boardFromNums("15153233665512265253266243367171");
    REQUIRE(solver.negamax(S) == -2);
  }
  SECTION("Test2") {
    State S = State::boardFromNums("25567612321766542715753451236");
    REQUIRE(solver.negamax(S) == 2);
  }
  SECTION("Test3") {
    State S = State::boardFromNums("2135616344362616617444333774221777125");
    REQUIRE(solver.negamax(S) == 2);
  }
  SECTION("Test4") {
    State S = State::boardFromNums("64261557453565765234637331431614777122");
    REQUIRE(solver.negamax(S) == 0);
  }
}
