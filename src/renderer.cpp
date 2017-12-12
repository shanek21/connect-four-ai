#include "../include/renderer.h"


int tileOffsets[7] = {2, 6, 10, 14, 18, 22, 26};

void displayGrid(State s) {
  mvaddstr(Y_OFFSET, X_OFFSET, "=============================");
  for (int y = Y_OFFSET + 1; y <= Y_OFFSET + State::HEIGHT + 1; y++) {
    mvaddstr(y, X_OFFSET, "|   |   |   |   |   |   |   |");
  }
  for (int row = 0; row < State::HEIGHT; row++) {
    for (int col = 0; col < State::WIDTH; col++) {
      State::TileType tileType = s.getTile(row, col);
      if (tileType == State::Red) {
        attron(COLOR_PAIR(1) | A_BOLD);
        mvaddch(Y_OFFSET + row + 1, X_OFFSET + tileOffsets[col], '@');
        attroff(COLOR_PAIR(1) | A_BOLD);
      }
      if (tileType == State::Black) {
        attron(COLOR_PAIR(2) | A_BOLD);
        mvaddch(Y_OFFSET + row + 1, X_OFFSET + tileOffsets[col], '@');
        attroff(COLOR_PAIR(2) | A_BOLD);
      }
    }
  }
  mvaddstr(Y_OFFSET + State::HEIGHT + 1, X_OFFSET,
      "=============================");
  refresh();
}

void setUpScreen() {
  initscr();                                // Start curses mode
  start_color();
  noecho();
  init_pair(1, COLOR_RED, COLOR_WHITE);     // Creates red tiles
  init_pair(2, COLOR_BLACK, COLOR_WHITE);   // Creates yellow tiles
  init_pair(3, 244, COLOR_WHITE);
  bkgd(COLOR_PAIR(3));
  mvaddstr(Y_OFFSET, X_OFFSET, "=============================");
  for (int y = Y_OFFSET + 1; y <= Y_OFFSET + State::HEIGHT + 1; y++) {
    mvaddstr(y, X_OFFSET, "|   |   |   |   |   |   |   |");
  }
  mvaddstr(Y_OFFSET + State::HEIGHT + 1, X_OFFSET,
      "=============================");
  refresh();
}

void shutDownScreen() {
  getch();                                  // Wait for user input
  endwin();                                 // End curses mode
}
