#include "main.h"

#include "gameplay.h"
#include "init_game.h"
#include "print_field.h"

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
  cbreak();
  // nodelay(stdscr, TRUE);
  timeout(100);
}

void playGame() {
  GameInfo_t game_state;
  current_block_t figure;

  //WINDOW *win = newwin(FIELD_SIZE_Y + 2, FIELD_SIZE_X + 2, 5, 5);

  init_game(&game_state);

  int command_code = 0;

  do {
    init_current_block(&game_state, &figure);

    // print_field(win, &figure, &game_state);

    clear();
    printw("block: x = %d, y = %d\n\n", figure.x, figure.y);
    print_matrix(&figure, &game_state);
    refresh();

    if ((command_code = getch())) {
      printw("$");
      do_users_command(command_code, &figure);
    }
      if (figure.y < FIELD_SIZE_Y) {
        (figure.y)++;

        printw("$$");
      }

    printw("$$$");

  } while (command_code != 27);

  //delwin(win);
}