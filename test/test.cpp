// This tells Catch to provide a main() - only do this in one cpp file
#include "../lib/catch.hpp"
#include "../include/add_numbers.h"

TEST_CASE("Numbers are added together") {
  REQUIRE(add_numbers(1, 2) == 3);
  REQUIRE(add_numbers(5, 3) == 8);
}
