/**
 * @file init_game.c
 * @brief file for the game initialization
 *
 */

#include "init_game.h"

/**
 * @brief Creates a 2D matrix of integers.
 *
 * This function allocates memory for a 2D matrix with the specified number of
 * rows and columns. If the allocation is successful, the matrix is initialized
 * to zero. If the allocation fails at any point, the function cleans up any
 * previously allocated memory and returns an error status.
 *
 * @param result A pointer to a pointer to the matrix that will be created. The
 * function will allocate memory and assign the address of the matrix to this
 * pointer.
 * @param rows The number of rows in the matrix. Must be greater than zero.
 * @param cols The number of columns in the matrix. Must be greater than zero.
 * @return A matrix_status indicating the result of the operation:
 *         - NORM: The matrix was created successfully.
 *         - MEMORY_ERROR: There was an error allocating memory.
 */
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

/**
 * @brief Retrieves the high score from a file.
 *
 * This function attempts to read the high score from a specified text file. If
 * the file is successfully opened and the score is read, it returns the score.
 * If there is an error reading the score or if the file does not exist, it
 * returns 0.
 *
 * @return The high score as an integer. Returns 0 if there is an error reading
 * the score.
 */
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

/**
 * @brief Initializes the game state.
 *
 * This function sets up the initial state of the game, including speed, level,
 * pause status, score, and high score. It also creates the necessary matrices
 * for the game field and blocks. If the matrix creation is successful, the game
 * state is set to START; otherwise, it is set to GAME_OVER.
 */
void init_game() {
  BackGameInfo_t *game_state = get_game_state();

  game_state->speed = 1;
  game_state->level = 1;
  game_state->pause = 0;
  game_state->score = 0;
  game_state->high_score = get_high_score();

  matrix_status field_status =
      create_matrix(&game_state->field, FIELD_SIZE_Y, FIELD_SIZE_X);

  matrix_status next_block_status =
      create_matrix(&game_state->next_block, BLOCK_SIZE, BLOCK_SIZE);

  matrix_status current_block_status =
      create_matrix(&game_state->figure.matrix, BLOCK_SIZE, BLOCK_SIZE);

  if (field_status + next_block_status + current_block_status == NORM) {
    game_state->fsm_state = START;
  } else {
    game_state->fsm_state = GAME_OVER;
  }
}