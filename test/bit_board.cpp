#include "../lib/catch.hpp"
#include "../include/bit_board.h"


TEST_CASE("get()") {
  BitBoard bb;
  bb.set(HEIGHT - 2, WIDTH - 1);
  REQUIRE(bb.get(HEIGHT - 2, WIDTH - 1) == 1);
}

/*
TEST_CASE("get()") {
  SECTION("simple case") {
    State s1;
    State s2 = s1.play(State::TileType::Red, 1);
    REQUIRE(s1.getTile(State::HEIGHT - 1, 1) == State::TileType::Empty);
    REQUIRE(s2.getTile(State::HEIGHT - 1, 1) == State::TileType::Red);
    REQUIRE(s2.isRedTile(State::HEIGHT - 1, 1));
    REQUIRE(!s2.isBlackTile(State::HEIGHT - 1, 1));
  }
  SECTION("complex case") {
    State S;
    S = S.play(1);
    S = S.play(0);
    S = S.play(2);
    S = S.play(1);
    S = S.play(2);
    S = S.play(2);
    S = S.play(3);
    S = S.play(3);
    S = S.play(3);
    REQUIRE(S.isBlackTile(State::HEIGHT - 1, 0));
    REQUIRE(S.isRedTile(State::HEIGHT - 1, 1));
    REQUIRE(S.isBlackTile(State::HEIGHT - 2, 1));
    REQUIRE(S.isRedTile(State::HEIGHT - 1, 2));
    REQUIRE(S.isRedTile(State::HEIGHT - 2, 2));
    REQUIRE(S.isBlackTile(State::HEIGHT - 3, 2));
    REQUIRE(S.isRedTile(State::HEIGHT - 1, 3));
    REQUIRE(S.isBlackTile(State::HEIGHT - 2, 3));
    REQUIRE(S.isRedTile(State::HEIGHT - 3, 3));
  }
}
*/
