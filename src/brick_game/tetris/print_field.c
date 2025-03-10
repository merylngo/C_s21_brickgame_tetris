#include "print_field.h"

void print_field(current_block_t *figure, GameInfo_t *game_state)
{
  for (int i = 0; i < FIELD_SIZE_X; i++) {
    mvaddch(BORDER_UP, i + BORDER_LEFT, '-');
  }

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    mvaddch(i + 1 + BORDER_UP, BORDER_LEFT, '|');

    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (figure->y == i && figure->x == j) {
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