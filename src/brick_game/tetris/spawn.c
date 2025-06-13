/**
 * @file spawn.c
 * @brief file for spawn logic
 *
 */

#include "spawn.h"

/**
 * @brief Copies a matrix from a source 2D array to a destination 3D array.
 *
 * This function takes a source matrix and copies its contents into a
 * destination matrix. The destination matrix is expected to be allocated and
 * passed as a pointer to a pointer.
 *
 * @param src The source matrix to copy from, a 2D array of integers.
 * @param dest A pointer to a 3D array where the matrix will be copied to.
 */
void copy_matrix(int src[][BLOCK_SIZE], int ***dest) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      (*dest)[i][j] = src[i][j];
    }
  }
}

/**
 * @brief Copies a matrix from a source 2D pointer array to a destination 3D
 * array.
 *
 * This function takes a source matrix represented as a pointer to a pointer and
 * copies its contents into a destination matrix. The destination matrix is
 * expected to be allocated and passed as a pointer to a pointer.
 *
 * @param src The source matrix to copy from, a pointer to a pointer of
 * integers.
 * @param dest A pointer to a 3D array where the matrix will be copied to.
 */
void copy_matrix_pt(int **src, int ***dest) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      (*dest)[i][j] = src[i][j];
    }
  }
}

/**
 * @brief Generates a random block code for the next block.
 *
 * This function generates a random block code from the available block codes.
 *
 * @return A randomly generated block code.
 */
void get_block(enum block_codes block_code, int ***block) {
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

/**
 * @brief Generates a random block code for the next block.
 *
 * This function generates a random block code from the available block codes.
 *
 * @return A randomly generated block code.
 */
enum block_codes generate_next_block() {
  return (enum block_codes)(rand() % 7);
}

/**
 * @brief Generates a random color code.
 *
 * This function generates a random color code for use in the game.
 *
 * @return A randomly generated color code.
 */
color_codes generate_color_code() { return (color_codes)(rand() % 7 + 1); }

/**
 * @brief Retrieves the next block and updates the game state.
 *
 * This function gets the next block based on the current game state and updates
 * the corresponding field in the game state structure.
 */
void get_next_block() {
  BackGameInfo_t *game_state = get_game_state();

  get_block(generate_next_block(), &game_state->next_block);
}

/**
 * @brief Initializes the current block in the game state.
 *
 * This function initializes the current block by copying the next block's
 * matrix into the current figure's matrix and sets its initial position and
 * color.
 */
void init_current_block() {
  BackGameInfo_t *game_state = get_game_state();

  copy_matrix_pt(game_state->next_block, &game_state->figure.matrix);

  game_state->figure.x = FIELD_SIZE_X / 2 - 1;
  game_state->figure.y = 0;

  game_state->figure.color = generate_color_code();
}

/**
 * @brief Spawns a new block in the game.
 *
 * This function handles the spawning of a new block in the game. It checks the
 * current state of the game and initializes the current block, then retrieves
 * the next block.
 */
void spawn_block() {
  BackGameInfo_t *game_state = get_game_state();

  if (game_state->fsm_state == START) {
    get_next_block();
  }

  game_state->fsm_state = SPAWN;

  init_current_block();
  get_next_block();

  game_state->fsm_state = MOVING;
}