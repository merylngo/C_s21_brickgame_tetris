#include "front_functions.h"

void userInput(UserAction_t action, bool hold) {
  (void)hold;

  switch (action) {
    case Left:
      break;

    case Right:
      break;

    case Down:
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