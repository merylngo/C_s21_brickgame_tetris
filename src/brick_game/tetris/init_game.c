#include "init_game.h"

matrix_status create_matrix(int ***result, int rows, int cols) {
  matrix_status status = NORM;

  if (rows <= 0 || cols <= 0) {
    status = MEMORY_ERROR;
  }

  if (status == NORM) {
    *result = (int **)malloc(rows * sizeof(int *));

    if (*result) {
      for (int i = 0; (i < rows) && (status == NORM); i++) {
        (*result)[i] = (int *)malloc(cols * sizeof(int));

        status = ((*result)[i]) ? NORM : MEMORY_ERROR;
      }
    } else {
      status = MEMORY_ERROR;
    }
  }

  if (status == NORM) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        (*result)[i][j] = 0;
      }
    }
  }

  return status;
}

void init_game() {
  BackGameInfo_t *game_state = get_game_state();

  matrix_status field_status =
      create_matrix(&game_state->field, FIELD_SIZE_Y, FIELD_SIZE_X);

  if (!game_state->field) return;

  matrix_status next_block_status =
      create_matrix(&game_state->next_block, BLOCK_SIZE, BLOCK_SIZE);

  if (!game_state->next_block) return;

  matrix_status current_block_status =
      create_matrix(&game_state->figure.matrix, BLOCK_SIZE, BLOCK_SIZE);

  if (!game_state->figure.matrix) return;

  if (field_status + next_block_status + current_block_status == 0) {
    game_state->fsm_state = START;
  }
}