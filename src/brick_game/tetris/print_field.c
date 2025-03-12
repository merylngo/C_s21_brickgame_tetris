#include "print_field.h"

void print_field(WINDOW *win, current_block_t *figure, GameInfo_t *game_state) {
  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if ((figure->y == i && figure->x == j) || game_state->field[i][j] == 1) {
        mvwaddch(win, j + 1, i + 1, '@');
      } else {
        mvwaddch(win, j + 1, i + 1, ' ');
      }
    }
  }
}