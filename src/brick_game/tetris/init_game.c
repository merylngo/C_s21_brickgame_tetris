#include "init_game.h"

int init_game(GameInfo_t *game_state) {
  matrix_memory_status field_status = create_field_matrix(game_state);

  game_state->next_block = '@';

  return 0;
}

matrix_memory_status create_field_matrix(GameInfo_t *game_state) {
  matrix_memory_status status = NORM;

  game_state->field = (int *)malloc(FIELD_SIZE_Y * sizeof(int *));

  if (status == NORM) {
    for (int i = 0; (i < FIELD_SIZE_Y) && (status == NORM); i++) {
      game_state->field[i] = (int *)malloc(FIELD_SIZE_X * sizeof(int));
      status = (game_state->field[i]) ? NORM : MEMORY_ERROR;
    }
  } else {
    status = MEMORY_ERROR;
  }

  if (status == NORM) {
    for (int i = 0; i < FIELD_SIZE_Y; i++) {
      for (int j = 0; j < FIELD_SIZE_Y; j++) {
        game_state->field[i][j] = 0;
      }
    }
  }

  return status;
}

void init_current_block(GameInfo_t *game_state, current_block_t *figure) {
  figure->figure_m = game_state->next_block;
  figure->x = FIELD_SIZE_X / 2;
  figure->y = BORDER_UP + 1;
}