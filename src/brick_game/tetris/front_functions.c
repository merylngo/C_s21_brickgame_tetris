#include "front_functions.h"

void userInput(UserAction_t action, int hold) {
  (void)hold;
  BackGameInfo_t *game_state = get_game_state();

  if (action == Start) {
    init_game();
  }

  switch (action) {
    case Left:
      if (game_state->fsm_state == MOVING) {
        move_left();
      }
      break;

    case Right:
      if (game_state->fsm_state == MOVING) {
        move_right();
      }
      break;

    case Down:
      if (game_state->fsm_state == MOVING) {
        fall_down();
      }

    case Action:
      if (game_state->fsm_state == MOVING) {
        turn_left();
      }

      break;
  }
}

// копирование из static структуры которая нужна в бэкенде и описывает всю игру
GameInfo_t updateCurrentState() {
  GameInfo_t front_info;
  BackGameInfo_t *back_state = get_game_state();

  front_info.field = back_state->field;
  front_info.next_block = back_state->next_block;
  front_info.level = back_state->level;
  front_info.score = back_state->score;

  return front_info;
}