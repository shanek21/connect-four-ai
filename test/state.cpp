#include "../lib/catch.hpp"
#include "../include/state.h"


class TestState: public State {
 public:
  void setNumMoves(int n) {
    numMoves = n;
  }
};


TEST_CASE("play()") {
  State s1;
  State s2 = s1.play(State::TileType::Red, 1);
  REQUIRE(s1.getTile(State::HEIGHT - 1, 1) == State::TileType::Empty);
  REQUIRE(s2.getTile(State::HEIGHT - 1, 1) == State::TileType::Red);
}

TEST_CASE("isBoardFull()") {
  TestState s1;
  s1.setNumMoves(TestState::WIDTH * TestState::HEIGHT);
  REQUIRE(s1.isBoardFull() == true);
}

TEST_CASE("isWinningPlay()") {
  State S;
  SECTION("Horizontal") {
    S = S.play(State::TileType::Red, 0);
    S = S.play(State::TileType::Red, 1);
    S = S.play(State::TileType::Red, 2);
    REQUIRE(S.isWinningPlay(State::TileType::Red, 3) == true);
  }
}
