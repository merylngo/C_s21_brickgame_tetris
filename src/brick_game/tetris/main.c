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
  game_state_t game_state;

  init_game_state(&game_state);

  int command = 0;

  do {
    clear();

    printw("borders: left = %d\nup = %d\nbottom = %d\nright = %d\n",
           BORDER_LEFT, BORDER_UP, BORDER_BOTTOM, BORDER_RIGHT);
    printw("block: x = %d  y = %d\n", game_state.block_x, game_state.block_y);
    game_state.field_matrix[game_state.block_x][game_state.block_y] = 1;
    print_field(&game_state);

    if (game_state.block_y + BORDER_UP + 2 == BORDER_BOTTOM) {
      game_state.block_x = FIELD_SIZE_X / 2;
      game_state.block_y = 0;
    }

    if (((command = getch()) && command != 0)) {
      if (command == KEY_LEFT &&
          game_state.block_x + BORDER_LEFT > BORDER_LEFT + 1) {
        game_state.field_matrix[game_state.block_x][game_state.block_y] = 0;

        game_state.block_x--;
      }

      if (command == KEY_RIGHT &&
          game_state.block_x + BORDER_LEFT + 1 < BORDER_RIGHT) {
        game_state.field_matrix[game_state.block_x][game_state.block_y] = 0;
        game_state.block_x++;
      }
    }
    if (game_state.block_y + BORDER_UP + 2 < BORDER_BOTTOM) {
      game_state.field_matrix[game_state.block_x][game_state.block_y] = 0;
      game_state.block_y++;
    }
  } while (command != 27);  // 27 = ESC
}

void init_game_state(game_state_t *game_state) {
  game_state->state = START;
  // enum block_codes next_block;

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      game_state->field_matrix[i][j] = 0;
    }
  }

  // next_block = generate_next_block() + 1;

  game_state->block_x = FIELD_SIZE_X / 2;
  game_state->block_y = BORDER_UP + 1;
}

enum block_codes generate_next_block() { return SQUARE; }

void print_field(game_state_t *game_state) {
  for (int i = 0; i < FIELD_SIZE_X; i++) {
    mvaddch(BORDER_UP, i + BORDER_LEFT, '-');
  }

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    mvaddch(i + 1 + BORDER_UP, BORDER_LEFT, '|');

    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (game_state->field_matrix[i][j]) {
        mvaddch(j + 1 + BORDER_UP, i + BORDER_LEFT, '@');
      } else {
        mvaddch(j + 1 + BORDER_UP, i + BORDER_LEFT, ' ');
      }

      mvaddch(i + 1 + BORDER_UP, BORDER_RIGHT, '|');
    }

    for (int i = 0; i < FIELD_SIZE_X; i++) {
      mvaddch(BORDER_BOTTOM, i + 1 + BORDER_LEFT, '-');
    }
  }
}