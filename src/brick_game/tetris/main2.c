#include "main.h"

int main(void) {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  cbreak();  // Включаем режим немедленного ввода
  // nodelay(stdscr, TRUE);
  timeout(100);

  game_loop();

  endwin();

  return 0;
}

void game_loop() {
  GameInfo_t game_state;

  init_game(&game_state);

  int command = 0;

  do {
    clear();

  } while (command != 27);  // 27 = ESC
}

enum block_codes generate_next_block() { return SQUARE; }