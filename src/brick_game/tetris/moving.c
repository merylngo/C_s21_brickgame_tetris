#include "moving.h"

void move_left() {
  BackGameInfo_t *game_state = get_game_state();
  (game_state->figure.x)--;
}

int able_to_move_left() {
  BackGameInfo_t *game_state = get_game_state();
  int res = 1;

  if (game_state->figure.x == 0) {
    res = 0;
  } else {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        if (game_state->figure.matrix[i][j] &&
            game_state->field[(game_state->figure.x + i - 1) % FIELD_SIZE_Y]
                             [(game_state->figure.y + j) % FIELD_SIZE_X]) {
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

void move_right() {
  BackGameInfo_t *game_state = get_game_state();
  (game_state->figure.x)++;
}

int able_to_move_right() {
  BackGameInfo_t *game_state = get_game_state();
  int last_j;
  int flag = 0;

  for (last_j = BLOCK_SIZE - 1; last_j > 0; last_j--) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      if (game_state->figure.matrix[i][last_j]) {
        flag = 1;
        break;
      }
    }

    if (flag) break;
  }

  flag = 1;

  if (game_state->figure.x + last_j < FIELD_SIZE_X - 1) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < last_j; j++) {
        if (game_state->figure.matrix[i][j] &&
            game_state->field[(game_state->figure.y + i) % FIELD_SIZE_Y]
                             [(game_state->figure.x + last_j + j + 1) %
                              FIELD_SIZE_X]) {
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

void move_down() {
  BackGameInfo_t *game_state = get_game_state();
  game_state->figure.y++;
}

int able_to_move_down() {
  BackGameInfo_t *game_state = get_game_state();
  int last_i;
  int flag = 0;

  for (last_i = BLOCK_SIZE - 1; last_i > 0; last_i--) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game_state->figure.matrix[last_i][j] == 1) {
        flag = 1;
        break;
      }
    }

    if (flag) {
      break;
    }
  }

  flag = 1;

  if (game_state->figure.y + last_i < FIELD_SIZE_Y - 1) {
    for (int i = last_i; i >= 0; i--) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        if (game_state->figure.matrix[i][j] &&
            game_state->field[(game_state->figure.y + i + 1) % FIELD_SIZE_Y]
                             [(game_state->figure.x + j) % FIELD_SIZE_X]) {
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

void fall_down() {
  while (able_to_move_down()) {
    move_down();
  }
}

void turn_left() {
  BackGameInfo_t *game_state = get_game_state();
  int left_matrix[BLOCK_SIZE][BLOCK_SIZE] = {0};

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      left_matrix[BLOCK_SIZE - j - 1][i] = game_state->figure.matrix[i][j];
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      game_state->figure.matrix[i][j] = left_matrix[i][j];
    }
  }

  normalize_matrix(game_state->figure.matrix);
}

int able_to_turn_left() {
  BackGameInfo_t *game_state = get_game_state();
  int left_matrix[BLOCK_SIZE][BLOCK_SIZE] = {0};
  int res = 0;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      left_matrix[BLOCK_SIZE - j - 1][i] = game_state->figure.matrix[i][j];
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (left_matrix[i][j] && (i + game_state->figure.x < FIELD_SIZE_X) &&
          (j + game_state->figure.y < FIELD_SIZE_Y)) {
        if (game_state->field[j + game_state->figure.y]
                             [i + game_state->figure.x] == 0)
          res = 1;
      }
    }
  }

  return res;
}