#include <iostream>

#include "../include/state.h"
#include "../include/renderer.h"

int main() {
  State s1;
  s1 = setupScreen(s1);
  shutDownScreen();
}
