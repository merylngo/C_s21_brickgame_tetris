#ifndef INIT_GAME_H
#define INIT_GAME_H

#include "main.h"

typedef enum { NORM, MEMORY_ERROR } matrix_memory_status;

int get_memory_for_game(GameInfo_t *game_state);

matrix_memory_status create_field_matrix(GameInfo_t *game_state);
matrix_memory_status create_block_matrix(GameInfo_t *game_state);

void remove_matrix(int **matrix, int rows);

#endif