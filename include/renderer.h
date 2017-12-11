#ifndef INCLUDE_RENDERER_H_
#define INCLUDE_RENDERER_H_


#include <ncurses.h>
#include "./state.h"


#define Y_OFFSET 1
#define X_OFFSET 2

void displayGrid(State s);
void setUpScreen();
void shutDownScreen();


#endif  // INCLUDE_RENDERER_H_
