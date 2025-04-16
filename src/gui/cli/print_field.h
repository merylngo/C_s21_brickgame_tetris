#ifndef PRINT_FIELD_H
#define PRINT_FIELD_H

#include "main.h"

void init_colors();

void print_field(WINDOW *win, current_block_t *figure, GameInfo_t *game_state);

void print_cell(int color_code, int x, int y, char sign);

void print_matrix(current_block_t *figure);

void print_start_screen();
void print_pause_screen();
void print_final_screen();

#endif