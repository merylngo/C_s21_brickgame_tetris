#include "main.h"
#include "print_field.h"
#include "init_game.h"
#include "gameplay.h"

int main(void) {
  initCli();

  playGame();

  endwin();

  return 0;
}

void initCli() {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  cbreak();  // Включаем режим немедленного ввода
  // nodelay(stdscr, TRUE);
  timeout(100);
}

void playGame() {
  GameInfo_t game_state;
  current_block_t figure;

  WINDOW *win = newwin(FIELD_SIZE_Y + 2, FIELD_SIZE_X + 2, 5, 5);
  refresh();

  init_game(&game_state);

  int command_code = 0;

  do {
    //clear();
    
    init_current_block(&game_state, &figure);

    box(win, 0, 0);
    wrefresh(win);

    print_field(win, &figure, &game_state);

    box(win, 0, 0);
    wrefresh(win);

    if (((command_code = getch()) && command_code != 0)) {
      do_users_command(command_code, &figure);
    } else if (figure.y + BORDER_UP + 2 < BORDER_BOTTOM) {
      figure.y++;
    }

  } while (command_code != 27);  // 27 = ESC
}