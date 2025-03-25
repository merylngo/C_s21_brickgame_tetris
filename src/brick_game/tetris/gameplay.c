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
      sum_in_layer += game_state->field[i][j];
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
  return (enum block_codes)(rand() % 2);
}

void get_next_block(GameInfo_t *game_state) {
  get_block(generate_next_block(), game_state->next_block);
}

void init_current_block(GameInfo_t *game_state, current_block_t *figure) {
  figure->matrix = game_state->next_block;

  figure->x = FIELD_SIZE_X / 2 - 1;
  figure->y = 0;
}

void move_down(current_block_t *figure) { figure->y++; }

int able_to_move_down(current_block_t *figure, GameInfo_t *game_state) {
  int last_i;
  int flag = 0;

  for (last_i = BLOCK_SIZE - 1; last_i > 0; last_i--) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (figure->matrix[last_i][j] == 1) {
        flag = 1;
        break;
      }
    }

    if (flag) {
      break;
    }
  }

  flag = 1;

  if (figure->y + last_i < FIELD_SIZE_Y - 1) {
    for (int i = last_i; i >= 0; i--) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        if (figure->matrix[i][j] +
                game_state->field[figure->y + i + 1][figure->x + j] ==
            2) {
          flag = 0;
          break;
        }
      }
    }
  } else {
    flag = 0;
  }

  return flag;
}

void move_left(current_block_t *figure) { (figure->x)--; }

int able_to_move_left(current_block_t *figure, GameInfo_t *game_state) {
  int res = 1;

  if (figure->x == 0) {
    res = 0;
  } else {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        if (figure->matrix[j][i] +
                game_state->field[figure->y + j][figure->x + i - 1] ==
            2) {
          res = 0;
          break;
        }
      }

      if (res == 0) {
        break;
      }
    }
  }

  return res;
}

void move_right(current_block_t *figure) { (figure->x)++; }

int able_to_move_right(current_block_t *figure, GameInfo_t *game_state) {
  int last_j;
  int flag = 0;

  for (last_j = BLOCK_SIZE - 1; last_j > 0; last_j--) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      if (figure->matrix[i][last_j]) {
        flag = 1;
        break;
      }
    }

    if (flag) break;
  }

  flag = 1;

  if (figure->x + last_j < FIELD_SIZE_X - 1) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < last_j; j++) {
        if (figure->matrix[i][j] +
                game_state->field[figure->y + i][figure->x + last_j + j + 1] ==
            2) {
          flag = 0;
          break;
        }
      }
    }
  } else {
    flag = 0;
  }

  return flag;
}

void turn_left_matrix(current_block_t *figure) {
  int left_matrix[BLOCK_SIZE][BLOCK_SIZE] = {0};
  int first_layer_block = 0;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      left_matrix[BLOCK_SIZE - j - 1][i] = figure->matrix[i][j];
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      figure->matrix[i][j] = left_matrix[i][j];
    }
  }

  for (int j = 0; j < BLOCK_SIZE; j++) {
    first_layer_block += figure->matrix[0][j];
  }

  if (first_layer_block == 0) {
    for (int i = 1; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        figure->matrix[i - 1][j] = figure->matrix[i][j];
      }
    }

    for (int j = 0; j < BLOCK_SIZE; j++) {
      figure->matrix[BLOCK_SIZE - 1][j] = 0;
    }
  }
}

void do_users_command(int command_code, current_block_t *figure,
                      GameInfo_t *game_state) {
  switch (command_code) {
    case 3:
      turn_left_matrix(figure);
      break;
    case 4:
      if (able_to_move_left(figure, game_state)) {
        move_left(figure);
      }
      break;
    case 5:
      if (able_to_move_right(figure, game_state)) {
        move_right(figure);
      }
      break;

    default:
      break;
  }
}

void attach_block_on_field(current_block_t *figure, GameInfo_t *game_state) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (figure->matrix[i][j]) {
        game_state->field[figure->y + i][figure->x + j] = 1;
      }
    }
  }
}