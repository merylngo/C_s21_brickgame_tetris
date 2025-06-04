#ifndef INIT_GAME_H
#define INIT_GAME_H

#include "main_header.h"

typedef enum { NORM, MEMORY_ERROR } matrix_status;

matrix_status create_matrix(int ***result, int rows, int cols);

int get_high_score();

void init_game();

#endif