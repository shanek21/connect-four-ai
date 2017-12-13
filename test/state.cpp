#include <iostream>

#include "../lib/catch.hpp"
#include "../include/state.h"


class TestState: public State {
 public:
  void setNumMoves(int n) {
    numMoves = n;
  }
};


TEST_CASE("play()") {
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

TEST_CASE("getNextTileColor()") {
  State S;
  REQUIRE(S.getNextTileColor() == State::TileType::Red);
  S = S.play(3);
  REQUIRE(S.getNextTileColor() == State::TileType::Black);
  S = S.play(3);
  REQUIRE(S.getNextTileColor() == State::TileType::Red);
}

TEST_CASE("isPlayable()") {
  State S;
  REQUIRE(S.isPlayable(0));
  for (int i = 0; i < State::HEIGHT; i++) {
    REQUIRE(S.isPlayable(0));
    S = S.play(0);
  }
  REQUIRE(!S.isPlayable(0));
  REQUIRE(S.isPlayable(1));
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
    REQUIRE(S.isWinningPlay(State::TileType::Red, 0) == false);
    REQUIRE(S.isWinningPlay(State::TileType::Red, 4) == false);
    REQUIRE(S.isWinningPlay(State::TileType::Red, 5) == false);
    REQUIRE(S.isWinningPlay(State::TileType::Red, 6) == false);
    REQUIRE(S.isWinningPlay(State::TileType::Red, 3) == true);
  }

  SECTION("Horizontal wrap around case") {
    S = S.play(State::TileType::Black, 5);
    S = S.play(State::TileType::Black, 6);
    S = S.play(State::TileType::Red, 5);
    S = S.play(State::TileType::Red, 6);
    S = S.play(State::TileType::Red, 0);
    REQUIRE(S.isWinningPlay(State::TileType::Red, 1) == false);
  }

  SECTION("Vertical") {
    S = S.play(0);
    S = S.play(1);
    S = S.play(0);
    S = S.play(1);
    S = S.play(0);
    S = S.play(2);
    REQUIRE(S.isWinningPlay(State::TileType::Red, 0));
    REQUIRE(!S.isWinningPlay(State::TileType::Red, 1));
    REQUIRE(!S.isWinningPlay(State::TileType::Red, 2));
    REQUIRE(!S.isWinningPlay(State::TileType::Red, 3));
  }

  SECTION("Vertical wrap around case") {
    State S;
    S = S.play(State::TileType::Red, 0);
    S = S.play(State::TileType::Red, 0);
    S = S.play(State::TileType::Black, 0);
    S = S.play(State::TileType::Black, 0);
    S = S.play(State::TileType::Red, 0);
    S = S.play(State::TileType::Red, 0);
    S = S.play(State::TileType::Red, 1);
    REQUIRE(!S.isWinningPlay(State::TileType::Red, 1));
  }

  SECTION("Diagonal rising") {
    S = S.play(1);
    REQUIRE(!S.isWinningPlay(State::TileType::Black, 6));
    S = S.play(0);
    S = S.play(2);
    S = S.play(1);
    S = S.play(2);
    S = S.play(2);
    S = S.play(3);
    REQUIRE(!S.isWinningPlay(State::TileType::Black, 3));
    S = S.play(3);
    S = S.play(3);
    REQUIRE(S.isWinningPlay(State::TileType::Black, 3));
  }

  SECTION("Diagonal falling") {
    S = S.play(State::TileType::Black, 0);
    S = S.play(State::TileType::Black, 0);
    S = S.play(State::TileType::Black, 0);
    S = S.play(State::TileType::Red, 0);

    S = S.play(State::TileType::Black, 1);
    S = S.play(State::TileType::Black, 1);
    S = S.play(State::TileType::Red, 1);

    S = S.play(State::TileType::Red, 3);

    S = S.play(State::TileType::Black, 2);
    REQUIRE(!S.isWinningPlay(State::TileType::Red, 0));
    REQUIRE(!S.isWinningPlay(State::TileType::Red, 1));
    REQUIRE(!S.isWinningPlay(State::TileType::Red, 3));
    REQUIRE(S.isWinningPlay(State::TileType::Red, 2));
  }
}

TEST_CASE("boardFromNums()") {
  State S = State::boardFromNums("123123");
  REQUIRE(S.getTile(State::HEIGHT - 1, 0) == State::TileType::Red);
  REQUIRE(S.getTile(State::HEIGHT - 2, 0) == State::TileType::Black);
  REQUIRE(S.getTile(State::HEIGHT - 1, 1) == State::TileType::Black);
  REQUIRE(S.getTile(State::HEIGHT - 2, 1) == State::TileType::Red);
  REQUIRE(S.getTile(State::HEIGHT - 1, 2) == State::TileType::Red);
  REQUIRE(S.getTile(State::HEIGHT - 2, 2) == State::TileType::Black);
}

TEST_CASE("winningPositions()") {
  State S = State::boardFromNums("113141476644");
  State::TileBoard redWins = S.winningPositions(State::TileType::Red);
  State::TileBoard blackWins = S.winningPositions(State::TileType::Black);
  REQUIRE(redWins.count() == 2);
  REQUIRE(blackWins.count() == 2);
  REQUIRE(State::hasTile(redWins, 5, 1));
  REQUIRE(State::hasTile(redWins, 5, 4));
  REQUIRE(State::hasTile(blackWins, 3, 4));
  REQUIRE(State::hasTile(blackWins, 1, 0));
}
