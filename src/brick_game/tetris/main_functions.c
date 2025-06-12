#include "free_game.h"
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
    free_game();
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

GameInfo_t UpdateCurrentState() {
  BackGameInfo_t *game_state = get_game_state();
  GameInfo_t *game_info = NULL;

  game_info = (GameInfo_t *)malloc(sizeof(GameInfo_t));

  game_info->level = game_state->level;
  game_info->speed = game_state->speed;
  game_info->high_score = game_state->high_score;
  game_info->score = game_state->score;
  game_info->pause = game_state->pause;

  matrix_status field_status =
      create_matrix(&game_info->field, FIELD_SIZE_Y, FIELD_SIZE_X);
  matrix_status next_block_status =
      create_matrix(&game_info->next, BLOCK_SIZE, BLOCK_SIZE);

  if (field_status == NORM && next_block_status == NORM) {
    for (int i = 0; i < FIELD_SIZE_Y; i++) {
      for (int j = 0; j < FIELD_SIZE_X; j++) {
        game_info->field[i][j] = game_state->field[i][j];
      }
    }

    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        if (game_state->figure.matrix[i][j]) {
          game_info->field[(game_state->figure.y + i) % FIELD_SIZE_Y]
                          [(game_state->figure.x + j) % FIELD_SIZE_X] =
              (int)game_state->figure.color;
        }
      }
    }

    copy_matrix_pt(game_state->next_block, &game_info->next);
  } else {
    game_state->fsm_state = GAME_OVER;
  }

  return *game_info;
}