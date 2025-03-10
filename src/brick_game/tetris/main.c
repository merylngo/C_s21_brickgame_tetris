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
  current_block_t figure;

  init_game(&game_state);

  int command_code = 0;

  do {
    clear();

    init_current_block(&game_state, &figure);

    print_field(&figure, &game_state);

    if (((command_code = getch()) && command_code != 0)) {
      do_users_command(command_code, &figure);
    } else if (figure.y + BORDER_UP + 2 < BORDER_BOTTOM) {
      figure.y++;
    }

  } while (command_code != 27);  // 27 = ESC
}