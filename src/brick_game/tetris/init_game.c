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

        if (status == MEMORY_ERROR) {
          for (int j = 0; j < i; j++) {
            free((*result)[j]);
          }

          free(*result);
          *result = NULL;
        }
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

int get_high_score() {
  int res = 0;
  FILE *file_score = fopen("./brick_game/tetris/high_score.txt", "r");

  if (file_score) {
    if (fscanf(file_score, "%d", &res) != 1) {
      res = 0;
    }

    fclose(file_score);
  }

  return res;
}

void init_game() {
  BackGameInfo_t *game_state = get_game_state();

  game_state->speed = 1;
  game_state->level = 1;
  game_state->high_score = get_high_score();

  matrix_status field_status =
      create_matrix(&game_state->field, FIELD_SIZE_Y, FIELD_SIZE_X);

  matrix_status next_block_status =
      create_matrix(&game_state->next_block, BLOCK_SIZE, BLOCK_SIZE);

  matrix_status current_block_status =
      create_matrix(&game_state->figure.matrix, BLOCK_SIZE, BLOCK_SIZE);

  if (field_status + next_block_status + current_block_status == 0) {
    game_state->fsm_state = START;
  }
}