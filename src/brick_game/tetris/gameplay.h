#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "main.h"

void move_left(current_block_t *figure, GameInfo_t *game_state);
void move_right(current_block_t *figure, GameInfo_t *game_state);
void do_users_command(int command_code, current_block_t *figure,
                      GameInfo_t *game_state);

int able_to_move(current_block_t *figure, GameInfo_t *game_state);

void copy_top_layers(int layer_number, GameInfo_t *game_state);
void remove_full_layers(GameInfo_t *game_state);

#endif