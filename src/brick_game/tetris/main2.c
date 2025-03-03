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

int init_game(GameInfo_t *game_state);
int init_game(GameInfo_t *game_state) {
  enum matrix_memory_status status = NORM;

  game_state->field = (int *)malloc(FIELD_SIZE_Y * sizeof(int *));

  if (status == NORM) {
    for (int i = 0; (i < FIELD_SIZE_Y) && (status == NORM); i++) {
      game_state->field[i] = (int *)malloc(FIELD_SIZE_X * sizeof(int));
      status = (game_state->field[i]) ? NORM : MEMORY_ERROR;
    }
  } else {
    status = MEMORY_ERROR;
  }

  if (status == NORM) {
    for (int i = 0; i < FIELD_SIZE_Y; i++) {
      for (int j = 0; j < FIELD_SIZE_Y; j++) {
        game_state->field[i][j] = 0;
      }
    }
  }

  return status;
}

enum block_codes generate_next_block() { return SQUARE; }