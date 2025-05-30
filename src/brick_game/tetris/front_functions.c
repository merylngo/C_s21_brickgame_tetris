#include "front_functions.h"

UserAction_t get_action(char command) {
  UserAction_t action;

  switch (command) {
    case '\n':
      action = Start;
      break;
    case 'p':
      action = Pause;
      break;
    case 'KEY_LEFT':
      action = Left;
      break;
    case 'KEY_RIGHT':
      action = Right;
      break;
    case 'KEY_DOWN':
      action = Down;
      break;
    case 'KEY_UP':
      action = Action;
      break;

    default:
      break;
  }

  return action;
}

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
        move_down();
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