#include "init_game.h"
#include "main_header.h"
#include "moving.h"
#include "spawn.h"

void userInput(UserAction_t action, int hold) {
  (void)hold;
  BackGameInfo_t *game_state = get_game_state();

  if (action == Start) {
    init_game();
    spawn_block();
  } else if (action == Pause) {
    game_state->pause = !game_state->pause;
  } else if (action == Terminate) {
    game_state->fsm_state = GAME_OVER;
    // free_game(); - не делаем пока т к будет seg fault в print_final_screen
  } else {
    move_block(action);
  }
}

const BackGameInfo_t *updateCurrentState() {
  const BackGameInfo_t *game_state = get_game_state();
  return game_state;
}

BackGameInfo_t *get_game_state() {
  static BackGameInfo_t game_state = {0};

  return &game_state;
}