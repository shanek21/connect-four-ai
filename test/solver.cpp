#include <iostream>
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
    // This takes about 1.5 seconds
    // This is unsolvable (for now)
    /* S = State::boardFromNums("266674777"); */
    /* REQUIRE(solver.score(S) == 4); */
    /* S = State::boardFromNums(""); */
    /* REQUIRE(solver.score(S) > 0); */
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
  SECTION("Begin Easy") {
    /* State S = State::boardFromNums("32164625"); */
    /* REQUIRE(solver.score(S) == 11); */
    /* S = State::boardFromNums("6146"); */
    /* REQUIRE(solver.score(S) == 18); */
    /* S = State::boardFromNums("243335424257"); */
    /* REQUIRE(solver.score(S) == 12); */
    /* S = State::boardFromNums("5512243243536"); */
    /* REQUIRE(solver.score(S) == 13); */
    /* S = State::boardFromNums("22144426444"); */
    /* REQUIRE(solver.score(S) == 15); */
    /* S = State::boardFromNums("265756512"); */
    /* REQUIRE(solver.score(S) == -12); */
    /* S = State::boardFromNums("65444437612"); */
    /* REQUIRE(solver.score(S) == 13); */
    /* S = State::boardFromNums("17516442226766"); */
    /* REQUIRE(solver.score(S) == 8); */
    /* S = State::boardFromNums("7343363417254"); */
    /* REQUIRE(solver.score(S) == 14); */
    /* S = State::boardFromNums("74746315233"); */
    /* REQUIRE(solver.score(S) == 15); */
    /* S = State::boardFromNums("5654767662"); */
    /* REQUIRE(solver.score(S) == 13); */
    /* S = State::boardFromNums("74642572132"); */
    /* REQUIRE(solver.score(S) == 15); */
    /* S = State::boardFromNums("51756773145177"); */
    /* REQUIRE(solver.score(S) == -10); */
    /* S = State::boardFromNums("165746146225"); */
    /* REQUIRE(solver.score(S) == -11); */
    /* S = State::boardFromNums("1562527227511"); */
    /* REQUIRE(solver.score(S) == 13); */
    /* S = State::boardFromNums("43745416472735"); */
    /* REQUIRE(solver.score(S) == -13); */
    /* S = State::boardFromNums("42434653771434"); */
    /* REQUIRE(solver.score(S) == 9); */
    /* S = State::boardFromNums("1626434452343"); */
    /* REQUIRE(solver.score(S) == 13); */
    /* S = State::boardFromNums("6513243566177"); */
    /* REQUIRE(solver.score(S) == 12); */
    /* S = State::boardFromNums("43623536647361"); */
    /* REQUIRE(solver.score(S) == 11); */
    /* S = State::boardFromNums("35544262"); */
    /* REQUIRE(solver.score(S) == 12); */
    /* S = State::boardFromNums("33375546411"); */
    /* REQUIRE(solver.score(S) == -12); */
    State S = State::boardFromNums("427631264721");
    REQUIRE(solver.score(S) == 10);
    /* S = State::boardFromNums("51615567"); */
    /* REQUIRE(solver.score(S) == 15); */
    /* S = State::boardFromNums("543772563551"); */
    /* REQUIRE(solver.score(S) == 14); */
    /* S = State::boardFromNums("27534134362633"); */
    /* REQUIRE(solver.score(S) == 10); */
    /* S = State::boardFromNums("7234472553"); */
    /* REQUIRE(solver.score(S) == 10); */
    /* S = State::boardFromNums("6126741462153"); */
    /* REQUIRE(solver.score(S) == 14); */
    /* S = State::boardFromNums("4737"); */
    /* REQUIRE(solver.score(S) == 18); */
    /* S = State::boardFromNums("7675456251"); */
    /* REQUIRE(solver.score(S) == 13); */
  }
  SECTION("Begin Medium") {
    /* State S = State::boardFromNums("335662333565"); */
    /* REQUIRE(solver.score(S) == -2); */
    /* S = State::boardFromNums("157564142155"); */
    /* REQUIRE(solver.score(S) == -5); */
  }
}

TEST_CASE("heuristicMoveOrder()") {
  Solver solver;
  State S = State::boardFromNums("1235361");
  std::vector<int> order = solver.heuristicMoveOrder(S);
  REQUIRE(order[0] == 3);
  REQUIRE(order[1] == 6);
  S = S.play(5);
  order = solver.heuristicMoveOrder(S);
  REQUIRE(order[0] == 2);
  REQUIRE(order[1] == 1);
  REQUIRE(order[2] == 0);
  S = State::boardFromNums("");
  order = solver.heuristicMoveOrder(S);
  REQUIRE(order[0] == 3);
}
