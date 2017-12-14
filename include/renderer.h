#ifndef INCLUDE_RENDERER_H_
#define INCLUDE_RENDERER_H_


#include <ncurses.h>
#include <string>
#include "./state.h"


#define Y_OFFSET 1
#define X_OFFSET 2

#define GRID_W   10
#define MENU_COL GRID_W+5
#define MENU_ROW 20

// Controls
#define UP_KEY     'k'
#define DOWN_KEY   'j'
#define LEFT_KEY   'h'
#define RIGHT_KEY  'l'
#define QUIT_KEY   'q'
#define SELECT_KEY '\n'
#define HINT_KEY   '?'

State setupScreen(State s);
void shutDownScreen();
void gamePlay(State s);


#endif  // INCLUDE_RENDERER_H_
