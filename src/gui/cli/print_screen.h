#ifndef PRINT_FIELD_H
#define PRINT_FIELD_H

#include "main.h"

void init_colors();

void print_cell(int color_code, int x, int y, char sign);

void print_current_state(BackGameInfo_t *game_state);

void print_start_screen();
void print_field(BackGameInfo_t *game_state);
void print_info_screen(BackGameInfo_t *game_state);
void print_pause_screen(BackGameInfo_t *game_state);
void print_final_screen(BackGameInfo_t *game_state);

#endif