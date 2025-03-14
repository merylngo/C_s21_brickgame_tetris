#ifndef INIT_GAME_H
#define INIT_GAME_H

#include "main.h"

typedef enum {
  NORM,
  INCORRECT_MATRIX,  // Ошибка, некорректная матрица
  MEMORY_ERROR,
} matrix_memory_status;

int init_game(GameInfo_t *game_state);
matrix_memory_status create_field_matrix(GameInfo_t *game_state);
void init_current_block(GameInfo_t *game_state, current_block_t *figure);
enum block_codes generate_next_block();

#endif