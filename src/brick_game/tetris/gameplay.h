#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "../../gui/cli/main.h"

void normalize_matrix(current_block_t *figure);
void turn_left_matrix(current_block_t *figure);
void move_left(current_block_t *figure);
void move_right(current_block_t *figure);
void move_down(current_block_t *figure);

int able_to_turn(current_block_t *figure, GameInfo_t *game_state);
int able_to_move_left(current_block_t *figure, GameInfo_t *game_state);
int able_to_move_right(current_block_t *figure, GameInfo_t *game_state);
int able_to_move_down(current_block_t *figure, GameInfo_t *game_state);

void do_users_command(int command_code, current_block_t *figure,
                      GameInfo_t *game_state);

void attach_block_on_field(current_block_t *figure, GameInfo_t *game_state);

void copy_top_layers(int layer_number, GameInfo_t *game_state);
void remove_full_layers(GameInfo_t *game_state);

void init_current_block(GameInfo_t *game_state, current_block_t *figure);

void copy_matrix(int src[][BLOCK_SIZE], int **dest);
enum block_codes generate_next_block();
void get_block(enum block_codes block_code, int **block);
void get_next_block(GameInfo_t *game_state);

int game_is_over(current_block_t *figure, GameInfo_t *game_state);

void userInput(UserAction_t action, bool hold);

#endif