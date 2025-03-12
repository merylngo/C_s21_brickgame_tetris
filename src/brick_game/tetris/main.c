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
  timeout(300);
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

    print_field(win, &figure, &game_state);

    box(win, 0, 0);
    wrefresh(win);

    if (((command_code = getch()) && command_code != 0)) {
      do_users_command(command_code, &figure);
    }
    
    if (figure.y < FIELD_SIZE_Y) {
      (figure.y)++;
    }

     printw("block: x = %d  y = %d\n", figure.x, figure.y);

  } while (command_code != 27);  // 27 = ESC
}