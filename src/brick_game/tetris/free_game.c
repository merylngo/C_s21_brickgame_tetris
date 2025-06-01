#include "free_game.h"

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

void free_game() {
  BackGameInfo_t *game_state = get_game_state();

  remove_matrix(&game_state->field, FIELD_SIZE_Y);
  remove_matrix(&game_state->next_block, BLOCK_SIZE);
  remove_matrix(&game_state->figure.matrix, BLOCK_SIZE);
}