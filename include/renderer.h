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
#define UP_KEY 'k'
#define DOWN_KEY 'j'
#define LEFT_KEY 'h'
#define RIGHT_KEY 'l'
#define PAUSE_KEY 'p'
#define QUIT_KEY 'q'
#define RESUME_KEY 'r'
#define SELECT_KEY '\n'


void renderMenu(const char* title,
                const char** items,
                int num_items,
                int selection);
void displayGrid(State s);
State setupScreen(State s);
void shutDownScreen();


#endif  // INCLUDE_RENDERER_H_
