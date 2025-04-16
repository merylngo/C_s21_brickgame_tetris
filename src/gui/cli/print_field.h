#ifndef PRINT_FIELD_H
#define PRINT_FIELD_H

#include "main.h"

#define GREEN_BCGR "\033[42m"
#define RED_BCGR "\033[31m"
#define YELLOW_BCGR "\033[43m \033[30m"
#define WHITE_FONT "\033[97m"
#define RESET_COLORS "\033[0m"

void show_start_screen();
void show_pause_screen();

void init_colors();

void print_field(WINDOW *win, current_block_t *figure, GameInfo_t *game_state);

void print_cell(int color_code, int x, int y, char sign);

void print_matrix(current_block_t *figure, GameInfo_t *game_state);

#endif