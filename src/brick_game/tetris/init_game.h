#ifndef INIT_GAME_H
#define INIT_GAME_H

#include "main_header.h"

typedef enum { NORM, MEMORY_ERROR } matrix_memory_status;

matrix_memory_status get_field_memory();
matrix_memory_status get_next_block_memory();
matrix_memory_status get_current_block_memory();

int get_memory_for_game();
void init_game();

#endif