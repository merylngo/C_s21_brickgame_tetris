#include "front_functions.h"

void userInput(UserAction_t action, int hold) {
  (void)hold;
  BackGameInfo_t *game_state = get_game_state();

  switch (action) {
    case Start:
      init_game();
      spawn_block();

      break;

    case Left:
      if (game_state->fsm_state == MOVING ||
          game_state->fsm_state == SHIFTING) {
        move_left();
      }
      break;

    case Right:
      if (game_state->fsm_state == MOVING ||
          game_state->fsm_state == SHIFTING) {
        move_right();
      }
      break;

    case Down:
      if (game_state->fsm_state == MOVING ||
          game_state->fsm_state == SHIFTING) {
        fall_down();
      }
      break;

    case Action:
      if (game_state->fsm_state == MOVING ||
          game_state->fsm_state == SHIFTING) {
        turn_left();
      }
      break;

    case Pause:
      game_state->pause = !game_state->pause;
      break;

    case Terminate:
      game_state->fsm_state = GAME_OVER;
      // free_game(); - не делаем пока т к будет seg fault в print_final_screen
      break;

    case Empty:
      if (game_state->fsm_state == MOVING ||
          game_state->fsm_state == SHIFTING) {
        move_down();
        // game_state->fsm_state = SHIFTING;
      }

      break;

    default:
      break;
  }
}

BackGameInfo_t *updateCurrentState() {
  BackGameInfo_t *game_state = get_game_state();
  return game_state;
}