#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "main.h"

void move_left(current_block_t *figure);
void move_right(current_block_t *figure);
void do_users_command(int command_code, current_block_t *figure);

int able_to_move(current_block_t *figure, GameInfo_t *game_state);

#endif