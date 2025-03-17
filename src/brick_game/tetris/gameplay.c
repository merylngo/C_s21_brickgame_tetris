#include "gameplay.h"

void move_left(current_block_t *figure) {
  if (figure->x > 1) {
    (figure->x)--;
  }
}
void move_right(current_block_t *figure) {
  if (figure->x < FIELD_SIZE_X) {
    (figure->x)++;
  }
}

void do_users_command(int command_code, current_block_t *figure) {
  switch (command_code) {
    case 4:
      move_left(figure);
      //mvprintw(25, 25, "$");
      break;
    case 5:
      move_right(figure);
      //mvprintw(25, 25, "$$");
      break;

    default:
      break;
  }
}

int able_to_move(current_block_t *figure, GameInfo_t *game_state) {
  return figure->x >= 1 && figure->x <= FIELD_SIZE_X && figure->y < FIELD_SIZE_Y &&
         game_state->field[(figure->y - 1) % FIELD_SIZE_Y][(figure->x - 1) % FIELD_SIZE_X] == 0;
}