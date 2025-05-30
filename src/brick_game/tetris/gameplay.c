#include "gameplay.h"

void copy_top_layers(int layer_number, GameInfo_t *game_state) {
  for (int i = layer_number; i > 0; i--) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      game_state->field[i][j] = game_state->field[i - 1][j];
    }
  }

  for (int j = 0; j < FIELD_SIZE_X; j++) {
    game_state->field[0][j] = 0;
  }
}

void remove_full_layers(GameInfo_t *game_state) {
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
      copy_top_layers(k, game_state);
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

void get_block(enum block_codes block_code, int **block) {
  if (block_code == SQUARE) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == LINE) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == RIGHT_ANGLE) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == LEFT_ANGLE) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == ZET) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == TURNED_ZET) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == TURNED_T) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }
}

enum block_codes generate_next_block() {
  return (enum block_codes)(rand() % 7);
}

color_codes generate_color_code() { return (color_codes)(rand() % 5 + 1); }

void get_next_block(GameInfo_t *game_state) {
  get_block(generate_next_block(), game_state->next_block);
}

void init_current_block(GameInfo_t *game_state, current_block_t *figure) {
  figure->matrix = game_state->next_block;

  figure->x = FIELD_SIZE_X / 2 - 1;
  figure->y = 0;

  figure->color = generate_color_code();
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

void attach_block_on_field(current_block_t *figure, GameInfo_t *game_state) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (figure->matrix[i][j]) {
        game_state->field[(figure->y + i) % FIELD_SIZE_Y]
                         [(figure->x + j) % FIELD_SIZE_X] = (int)figure->color;
      }
    }
  }
}

int game_is_over(current_block_t *figure, GameInfo_t *game_state) {
  int last_i;
  int cnt_empty_strings = 0;

  for (last_i = BLOCK_SIZE - 1; last_i > 0; last_i--) {
    int j;

    for (j = 0; j < BLOCK_SIZE; j++) {
      if (figure->matrix[last_i][j]) {
        break;
      }
    }

    if (figure->matrix[last_i][j]) {
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