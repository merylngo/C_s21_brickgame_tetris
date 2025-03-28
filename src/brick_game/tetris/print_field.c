#include "print_field.h"

void print_matrix(current_block_t *figure, GameInfo_t *game_state) {
  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (game_state->field[i][j]) {
        mvaddch(i, j, '#');
      } else {
        mvaddch(i, j, '-');
      }
    }

    printw("%d", i);
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++)
      if (figure->matrix[i][j]) {
        mvaddch(figure->y + i, figure->x + j, 'o');
      }
  }
}