/**
 * @file free_game.c
 * @brief file for the freeing game resourses
 *
 */

#include "free_game.h"

/**
 * @brief Deallocates memory for a 2D matrix.
 *
 * This function frees the memory allocated for a 2D matrix of integers. It
 * iterates through each row of the matrix, freeing the memory for each row, and
 * then frees the memory for the matrix itself. After deallocation, it sets the
 * matrix pointer to NULL to avoid dangling pointers.
 *
 * @param matrix A pointer to a pointer to the matrix to be deallocated. The
 * function will modify this pointer to NULL after freeing the memory.
 * @param rows The number of rows in the matrix. This is used to iterate through
 * the matrix and free each row.
 */
void remove_matrix(int ***matrix, int rows) {
  if (*matrix) {
    for (int i = 0; i < rows; i++) {
      if ((*matrix)[i]) {
        free((*matrix)[i]);
      }
    }

    free(*matrix);
  }

  *matrix = NULL;
}

/**
 * @brief Frees all resources associated with the game.
 *
 * This function deallocates memory for the game state, including the game
 * field, the next block, and the current figure's matrix. It calls the
 * `remove_matrix` function for each of these components to ensure proper memory
 * management and prevent memory leaks.
 */
void free_game() {
  BackGameInfo_t *game_state = get_game_state();

  remove_matrix(&game_state->field, FIELD_SIZE_Y);
  remove_matrix(&game_state->next_block, BLOCK_SIZE);
  remove_matrix(&game_state->figure.matrix, BLOCK_SIZE);
}