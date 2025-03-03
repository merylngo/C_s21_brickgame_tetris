#include "gameplay.h"

void move_left(current_block_t *figure) {
  if (figure->x + BORDER_LEFT > BORDER_LEFT + 1) {
    figure->x--;
  }
}
void move_right(current_block_t *figure) {
  if (figure->x + BORDER_LEFT + 1 < BORDER_RIGHT) {
    figure->x++;
  }
}

void do_users_command(int command_code, current_block_t *figure) {
  switch (command_code) {
    case KEY_LEFT:
      move_left(figure);
      break;
    case KEY_RIGHT:
      move_right(figure);
      break;

    default:
      break;
  }
}