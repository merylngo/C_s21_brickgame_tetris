#include "gameplay.h"

void move_left(current_block_t *figure, GameInfo_t *game_state) {
  if (figure->x > 1 && game_state->field[figure->y - 1][figure->x - 2] == 0) {
    (figure->x)--;
  }
}

void move_right(current_block_t *figure, GameInfo_t *game_state) {
  if (figure->x < FIELD_SIZE_X &&
      game_state->field[figure->y - 1][figure->x] == 0) {
    (figure->x)++;
  }
}

void turn_left_matrix(current_block_t *figure) {
  int left_matrix[BLOCK_SIZE][BLOCK_SIZE] = {0};

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
}

void do_users_command(int command_code, current_block_t *figure,
                      GameInfo_t *game_state) {
  switch (command_code) {
    case 3:
      turn_left_matrix(figure);
      break;
    case 4:
      move_left(figure, game_state);
      break;
    case 5:
      move_right(figure, game_state);
      break;

    default:
      break;
  }
}

int able_to_move(current_block_t *figure, GameInfo_t *game_state) {
  return (figure->x >= 1 && figure->x <= FIELD_SIZE_X &&
          figure->y < FIELD_SIZE_Y) &&
         game_state->field[(figure->y - 1) % FIELD_SIZE_Y]
                          [(figure->x - 1) % FIELD_SIZE_X] == 0 &&
         game_state->field[(figure->y) % FIELD_SIZE_Y]
                          [(figure->x - 1) % FIELD_SIZE_X] == 0;
}

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
  return (enum block_codes)(rand() % 7);
}

void get_next_block(GameInfo_t *game_state) {
  get_block(generate_next_block(), game_state->next_block);
}

void init_current_block(GameInfo_t *game_state, current_block_t *figure) {
  figure->matrix = game_state->next_block;

  figure->x = FIELD_SIZE_X / 2;
  figure->y = 1;
}