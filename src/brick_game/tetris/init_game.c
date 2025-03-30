#include "init_game.h"

int get_memory_for_game(GameInfo_t *game_state) {
  matrix_memory_status field_status = create_field_matrix(game_state);
  matrix_memory_status block_status = create_block_matrix(game_state);

  return field_status + block_status;
}

matrix_memory_status create_field_matrix(GameInfo_t *game_state) {
  matrix_memory_status status = NORM;

  game_state->field = (int **)malloc(FIELD_SIZE_Y * sizeof(int *));

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
      for (int j = 0; j < FIELD_SIZE_X; j++) {
        game_state->field[i][j] = 0;
      }
    }
  }

  return status;
}

matrix_memory_status create_block_matrix(GameInfo_t *game_state) {
  matrix_memory_status status = NORM;

  game_state->next_block = (int **)malloc(BLOCK_SIZE * sizeof(int *));

  if (status == NORM) {
    for (int i = 0; (i < BLOCK_SIZE) && (status == NORM); i++) {
      game_state->next_block[i] = (int *)malloc(BLOCK_SIZE * sizeof(int));
      status = (game_state->next_block) ? NORM : MEMORY_ERROR;
    }
  } else {
    status = MEMORY_ERROR;
  }

  if (status == NORM) {
    for (int i = 0; i < FIELD_SIZE_Y; i++) {
      for (int j = 0; j < FIELD_SIZE_X; j++) {
        game_state->field[i][j] = 0;
      }
    }
  }

  return status;
}

void remove_matrix(int **matrix, int rows) {
  if (matrix) {
    for (int i = 0; i < rows; i++) {
      if (matrix[i]) {
        free(matrix[i]);
      }
    }

    free(matrix);
  }

  matrix = NULL;
}