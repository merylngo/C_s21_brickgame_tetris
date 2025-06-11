#ifndef MAIN_H_
#define MAIN_H_

#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../brick_game/tetris/attaching.h"
#include "../brick_game/tetris/free_game.h"
#include "../brick_game/tetris/init_game.h"
#include "../brick_game/tetris/main_header.h"
#include "../brick_game/tetris/moving.h"
#include "../brick_game/tetris/spawn.h"

#define GREEN_BCGR "\033[42m"
#define RED_BCGR "\033[31m"
#define YELLOW_BCGR "\033[43m \033[30m"
#define WHITE_FONT "\033[97m"
#define RESET_COLORS "\033[0m"

Suite* init_free_test(void);
Suite* attaching_test(void);
Suite* fall_down_test(void);
Suite* front_frunctions_test(void);
Suite* moving_test(void);
Suite* spawn_test(void);

void generate_field();
int check_block_on_field(int field_before[][FIELD_SIZE_X]);
int check_equality();
int equal_matrix(int** m1, int m2[][BLOCK_SIZE]);

int check_move_left(int x_prev, int y_prev);
int check_move_right(int x_prev, int y_prev);
int check_move_down(int x_prev, int y_prev);
int check_no_move(int x_prev, int y_prev);
int check_turn(int m[][BLOCK_SIZE]);

#endif
