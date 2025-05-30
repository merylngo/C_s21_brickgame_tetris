#include "main_header.h"

void copy_top_layers(int layer_number) {
  BackGameInfo_t *game_state = get_game_state();

  for (int i = layer_number; i > 0; i--) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      game_state->field[i][j] = game_state->field[i - 1][j];
    }
  }

  for (int j = 0; j < FIELD_SIZE_X; j++) {
    game_state->field[0][j] = 0;
  }
}

void remove_full_layers() {
  BackGameInfo_t *game_state = get_game_state();

  int layers[FIELD_SIZE_Y] = {0};

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    int sum_in_layer = 0;

    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (game_state->field[i][j]) {
        sum_in_layer++;
      }
    }

    if (sum_in_layer == FIELD_SIZE_X) {
      layers[i] = 1;
    }
  }

  for (int k = 0; k < FIELD_SIZE_Y; k++) {
    if (layers[k]) {
      copy_top_layers(k);
      layers[k] = 0;
    }
  }
}

void copy_matrix(int src[][BLOCK_SIZE], int **dest) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      dest[i][j] = src[i][j];
    }
  }
}

void normalize_matrix(int **matrix) {
  int first_layer_block = 0;

  for (int j = 0; j < BLOCK_SIZE; j++) {
    first_layer_block += matrix[0][j];
  }

  if (first_layer_block == 0) {
    for (int i = 1; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        matrix[i - 1][j] = matrix[i][j];
      }
    }

    for (int j = 0; j < BLOCK_SIZE; j++) {
      matrix[BLOCK_SIZE - 1][j] = 0;
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    first_layer_block += matrix[i][0];
  }

  if (first_layer_block == 0) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 1; j < BLOCK_SIZE; j++) {
        matrix[i][j - 1] = matrix[i][j];
      }
    }

    for (int i = 0; i < BLOCK_SIZE; i++) {
      matrix[i][BLOCK_SIZE - 1] = 0;
    }
  }
}

void attach_block_on_field() {
  BackGameInfo_t *game_state = get_game_state();

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game_state->figure.matrix[i][j]) {
        game_state->field[(game_state->figure.y + i) % FIELD_SIZE_Y]
                         [(game_state->figure.x + j) % FIELD_SIZE_X] =
            (int)game_state->figure.color;
      }
    }
  }
}

int game_is_over() {
  BackGameInfo_t *game_state = get_game_state();

  int last_i;
  int cnt_empty_strings = 0;

  for (last_i = BLOCK_SIZE - 1; last_i > 0; last_i--) {
    int j;

    for (j = 0; j < BLOCK_SIZE; j++) {
      if (game_state->figure.matrix[last_i][j]) {
        break;
      }
    }

    if (game_state->figure.matrix[last_i][j]) {
      break;
    }
  }

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    int cnt = 0;

    for (int j = 0; j < FIELD_SIZE_X; j++) {
      cnt += game_state->field[i][j];
    }

    if (cnt == 0) {
      cnt_empty_strings++;
    } else {
      break;
    }
  }

  return cnt_empty_strings >= last_i + 1;
}