#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "main_header.h"

void normalize_matrix(int **matrix);

void attach_block_on_field(current_block_t *figure, GameInfo_t *game_state);

void copy_top_layers(int layer_number, GameInfo_t *game_state);
void remove_full_layers(GameInfo_t *game_state);

void init_current_block(GameInfo_t *game_state, current_block_t *figure);

void copy_matrix(int src[][BLOCK_SIZE], int **dest);
enum block_codes generate_next_block();
color_codes generate_color_code();
void get_block(enum block_codes block_code, int **block);
void get_next_block(GameInfo_t *game_state);

int game_is_over(current_block_t *figure, GameInfo_t *game_state);

#endif