#include "init_game.h"

matrix_memory_status get_field_memory() {
  matrix_memory_status status = NORM;
  BackGameInfo_t *game_state = get_game_state();

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

matrix_memory_status get_next_block_memory() {
  BackGameInfo_t *game_state = get_game_state();
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
        game_state->next_block[i][j] = 0;
      }
    }
  }

  return status;
}

matrix_memory_status get_current_block_memory() {
  BackGameInfo_t *game_state = get_game_state();
  matrix_memory_status status = NORM;

  game_state->figure.matrix = (int **)malloc(BLOCK_SIZE * sizeof(int *));

  if (status == NORM) {
    for (int i = 0; (i < BLOCK_SIZE) && (status == NORM); i++) {
      game_state->figure.matrix[i] = (int *)malloc(BLOCK_SIZE * sizeof(int));
      status = (game_state->figure.matrix) ? NORM : MEMORY_ERROR;
    }
  } else {
    status = MEMORY_ERROR;
  }

  if (status == NORM) {
    for (int i = 0; i < FIELD_SIZE_Y; i++) {
      for (int j = 0; j < FIELD_SIZE_X; j++) {
        game_state->figure.matrix = 0;
      }
    }
  }

  return status;
}

int get_memory_for_game() {
  matrix_memory_status field_status = get_field_memory();
  matrix_memory_status next_block_status = get_next_block_memory();
  matrix_memory_status current_block_status = get_current_block_memory();

  return field_status + next_block_status + current_block_status;
}

void init_game() { get_memory_for_game(); }