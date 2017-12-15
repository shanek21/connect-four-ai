#include <iostream>

#include "../include/state.h"
#include "../include/solver.h"
#include "../include/renderer.h"

int main() {
  State s1 = State::boardFromNums("72324716156654");
  Solver solver;
  s1 = setupScreen(s1);
  gamePlay(s1, solver);
  shutDownScreen();
}
