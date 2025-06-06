#ifndef MAIN_H_
#define MAIN_H_

#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../brick_game/tetris/attaching.h"
#include "../brick_game/tetris/free_game.h"
#include "../brick_game/tetris/front_functions.h"
#include "../brick_game/tetris/init_game.h"
#include "../brick_game/tetris/main_header.h"
#include "../brick_game/tetris/moving.h"
#include "../brick_game/tetris/spawn.h"

#define GREEN_BCGR "\033[42m"
#define RED_BCGR "\033[31m"
#define YELLOW_BCGR "\033[43m \033[30m"
#define WHITE_FONT "\033[97m"
#define RESET_COLORS "\033[0m"

Suite* init_game_test(void);
Suite* fall_down_test(void);

void generate_field();
int check_block_on_field(int field_before[][FIELD_SIZE_X]);

#endif
