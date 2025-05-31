#include "front_functions.h"

void userInput(UserAction_t action, int hold) {
  (void)hold;
  BackGameInfo_t *game_state = get_game_state();

  printw("action == %d", action);

  switch (action) {
    case Start:
      game_state->fsm_state = START;
      init_game();
      game_state->fsm_state = SPAWN;
      spawn_block();
      game_state->fsm_state = MOVING;
      break;

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
      break;

    case Action:
      if (game_state->fsm_state == MOVING) {
        turn_left();
      }
      break;

    case Pause:
      game_state->pause = !game_state->pause;
      break;

    case Terminate:
      free_game();
      game_state->fsm_state = GAME_OVER;
      break;

    default:
      if (game_state->fsm_state == MOVING) {
        move_down();
      }
      break;
  }
}

BackGameInfo_t updateCurrentState() {
  BackGameInfo_t *game_state = get_game_state();
  return *game_state;
}