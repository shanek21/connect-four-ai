#ifndef INCLUDE_RENDERER_H_
#define INCLUDE_RENDERER_H_


#include <ncurses.h>
#include <string>
#include "./state.h"
#include "./solver.h"


#define Y_OFFSET 1
#define X_OFFSET 2

#define GRID_W   10
#define MENU_COL GRID_W+5
#define MENU_ROW 20
#define HINT_LIMIT 17

// Controls
#define UP_KEY     'k'
#define DOWN_KEY   'j'
#define LEFT_KEY   'h'
#define RIGHT_KEY  'l'
#define QUIT_KEY   'q'
#define SELECT_KEY '\n'
#define HINT_KEY   '?'

#define QUIT_GAME      -1

State setupScreen(State s);
void shutDownScreen();
void gamePlay(State s, Solver solver);


#endif  // INCLUDE_RENDERER_H_
