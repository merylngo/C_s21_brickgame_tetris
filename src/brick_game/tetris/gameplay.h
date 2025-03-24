#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "main.h"

void move_left(current_block_t *figure, GameInfo_t *game_state);
void move_right(current_block_t *figure, GameInfo_t *game_state);
void move_down(current_block_t *figure);

void do_users_command(int command_code, current_block_t *figure,
                      GameInfo_t *game_state);

void turn_left_matrix(current_block_t *figure);

int able_to_move_left(current_block_t *figure, GameInfo_t *game_state);
int able_to_move_right(current_block_t *figure, GameInfo_t *game_state);
int able_to_move_down(current_block_t *figure, GameInfo_t *game_state);
int able_to_move(current_block_t *figure, GameInfo_t *game_state);

void copy_top_layers(int layer_number, GameInfo_t *game_state);
void remove_full_layers(GameInfo_t *game_state);

void init_current_block(GameInfo_t *game_state, current_block_t *figure);

void copy_matrix(int src[][BLOCK_SIZE], int **dest);
enum block_codes generate_next_block();
void get_block(enum block_codes block_code, int **block);
void get_next_block(GameInfo_t *game_state);

#endif