/**
 * @file moving.c
 * @brief file for moving logic
 *
 */

#include "moving.h"

#include "attaching.h"
#include "main_header.h"

/**
 * @brief Checks if the current figure can move left.
 *
 * This function checks if the current figure can move left without colliding
 * with the walls or other blocks in the game field.
 *
 * @return 1 if the figure can move left, 0 otherwise.
 */
int able_to_move_left() {
  BackGameInfo_t *game_state = get_game_state();
  int res = 1;

  if (game_state->figure.x == 0) {
    res = 0;
  } else {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        if (game_state->figure.matrix[i][j] &&
            game_state->field[(game_state->figure.y + i) % FIELD_SIZE_Y]
                             [(game_state->figure.x + j - 1) % FIELD_SIZE_X]) {
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

/**
 * @brief Checks if the current figure can move right.
 *
 * This function checks if the current figure can move right without colliding
 * with the walls or other blocks in the game field.
 *
 * @return 1 if the figure can move right, 0 otherwise.
 */
int able_to_move_right() {
  BackGameInfo_t *game_state = get_game_state();
  int res = 1;
  int last_j = -1;

  for (int j = BLOCK_SIZE - 1; j >= 0; j--) {
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
      if (game_state->figure.matrix[i][j]) {
        last_j = j;
        break;
      }
    }

    if (last_j >= 0) {
      break;
    }
  }

  if (game_state->figure.x + last_j == FIELD_SIZE_X - 1) {
    res = 0;
  } else {
    for (int j = BLOCK_SIZE - 1; j >= 0; j--) {
      for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        if (game_state->figure.matrix[i][j] &&
            game_state->field[(game_state->figure.y + i) % FIELD_SIZE_Y]
                             [(game_state->figure.x + j + 1) % FIELD_SIZE_X]) {
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

/**
 * @brief Checks if the current figure can move down.
 *
 * This function checks if the current figure can move down without colliding
 * with the bottom of the game field or other blocks.
 *
 * @return 1 if the figure can move down, 0 otherwise.
 */
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

/**
 * @brief Normalizes a matrix by removing empty rows and columns.
 *
 * This function checks the first row and column of the matrix and removes them
 * if they are completely empty (sum of elements is zero). The remaining
 * elements are shifted accordingly.
 *
 * @param matrix The matrix to normalize, a 2D array of integers.
 */
void normalize_matrix(int matrix[][BLOCK_SIZE]) {
  int first_row_sum = 0;

  for (int j = 0; j < BLOCK_SIZE; j++) {
    first_row_sum += matrix[0][j];
  }

  if (first_row_sum == 0) {
    for (int i = 1; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        matrix[i - 1][j] = matrix[i][j];
      }
    }

    for (int j = 0; j < BLOCK_SIZE; j++) {
      matrix[BLOCK_SIZE - 1][j] = 0;
    }
  }

  int first_col_sum = 0;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    first_col_sum += matrix[i][0];
  }

  if (first_col_sum == 0) {
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

/**
 * @brief Checks if the current figure can turn left.
 *
 * This function checks if the current figure can be rotated 90 degrees to the
 * left without colliding with the walls or other blocks in the game field.
 *
 * @return 1 if the figure can turn left, 0 otherwise.
 */
int able_to_turn_left() {
  BackGameInfo_t *game_state = get_game_state();
  int left_matrix[BLOCK_SIZE][BLOCK_SIZE] = {0};
  int result = 1;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      left_matrix[BLOCK_SIZE - j - 1][i] = game_state->figure.matrix[i][j];
    }
  }

  normalize_matrix(left_matrix);
  normalize_matrix(left_matrix);
  normalize_matrix(left_matrix);

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (left_matrix[i][j] && (i + game_state->figure.y < FIELD_SIZE_Y) &&
          (j + game_state->figure.x < FIELD_SIZE_X)) {
        result *= (game_state->field[i + game_state->figure.y]
                                    [j + game_state->figure.x] == 0);
      } else if (left_matrix[i][j]) {
        result = 0;
      }
    }
  }

  return result;
}

/**
 * @brief Rotates the current figure's matrix 90 degrees to the left.
 *
 * This function rotates the current figure's matrix and normalizes it by
 * removing empty rows and columns.
 */
void turn_left_matrix() {
  BackGameInfo_t *game_state = get_game_state();
  int left_matrix[BLOCK_SIZE][BLOCK_SIZE] = {0};

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      left_matrix[BLOCK_SIZE - j - 1][i] = game_state->figure.matrix[i][j];
    }
  }

  normalize_matrix(left_matrix);
  normalize_matrix(left_matrix);
  normalize_matrix(left_matrix);

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      game_state->figure.matrix[i][j] = left_matrix[i][j];
    }
  }
}

/**
 * @brief Moves the current figure left if possible.
 *
 * This function attempts to move the current figure left. If it cannot move
 * down after moving left, it attaches the block to the game field.
 */
void move_down() {
  BackGameInfo_t *game_state = get_game_state();

  if (able_to_move_down()) {
    game_state->fsm_state = MOVING;
    (game_state->figure.y)++;
  } else {
    attach_block();
  }
}

/**
 * @brief Moves the current figure left if possible.
 *
 * This function attempts to move the current figure left. If it cannot move
 * down after moving left, it attaches the block to the game field.
 */
void move_left() {
  BackGameInfo_t *game_state = get_game_state();

  game_state->fsm_state = MOVING;

  if (able_to_move_left()) {
    (game_state->figure.x)--;
  }

  if (!able_to_move_down()) {
    attach_block();
  } else {
    // game_state->fsm_state = SHIFTING;
    // move_down();
  }
}

/**
 * @brief Moves the current figure right if possible.
 *
 * This function attempts to move the current figure right. If it cannot move
 * down after moving right, it attaches the block to the game field.
 */
void move_right() {
  BackGameInfo_t *game_state = get_game_state();

  game_state->fsm_state = MOVING;

  if (able_to_move_right()) {
    (game_state->figure.x)++;
  }

  if (!able_to_move_down()) {
    attach_block();
  } else {
    // game_state->fsm_state = SHIFTING;
    // move_down();
  }
}

/**
 * @brief Turns the current figure left if possible.
 *
 * This function attempts to rotate the current figure's matrix 90 degrees to
 * the left. If it cannot move down after turning, it attaches the block to the
 * game field.
 */
void turn_left() {
  // BackGameInfo_t *game_state = get_game_state();

  if (able_to_turn_left()) {
    turn_left_matrix();
  }

  if (!able_to_move_down()) {
    attach_block();
  } else {
    // game_state->fsm_state = SHIFTING;
    // move_down();
  }
}

/**
 * @brief Drops the current figure down to the lowest possible position.
 *
 * This function moves the current figure down until it can no longer move down,
 * then attaches the block to the game field.
 */
void fall_down() {
  while (able_to_move_down()) {
    move_down();
  }

  attach_block();
}

/**
 * @brief Moves the current block based on user action.
 *
 * This function processes user actions (left, right, down, turn) and moves the
 * current block accordingly. It checks the current state of the game before
 * executing the action.
 *
 * @param action The user action to perform.
 */
void move_block(UserAction_t action) {
  BackGameInfo_t *game_state = get_game_state();

  if (game_state->fsm_state == MOVING || game_state->fsm_state == SHIFTING) {
    switch (action) {
      case Left:
        move_left();
        break;

      case Right:
        move_right();
        break;

      case Down:
        fall_down();
        break;

      case Action:
        turn_left();
        break;

      case Empty:
        // game_state->fsm_state == SHIFTING;
        move_down();
        break;

      default:
        break;
    }
  }
}