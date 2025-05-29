#ifndef PRINT_FIELD_H
#define PRINT_FIELD_H

#include "main.h"

void init_colors();

void print_cell(int color_code, int x, int y, char sign);

void print_start_screen();
void print_matrix();
void print_info_screen();
void print_pause_screen();
void print_final_screen();

#endif