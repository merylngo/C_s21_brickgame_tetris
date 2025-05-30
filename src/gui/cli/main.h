#ifndef S21_MAIN_H
#define S21_MAIN_H

#include <ncurses.h>
#include <time.h>

#include "../../brick_game/tetris/free_game.h"
#include "../../brick_game/tetris/front_functions.h"
#include "../../brick_game/tetris/init_game.h"
#include "../../brick_game/tetris/main_header.h"
#include "../../brick_game/tetris/moving.h"
#include "print_screen.h"

#if 0
#define KEY_LEFT 260
#define KEY_RIGHT 261
#define KEY_UP 262
#define KEY_DOWN 263
#define KEY_ENTER 264
#define KEY_ESCAPE 265
#endif

void init_cli();
void play_game();

UserAction_t get_action(char command);
int game_not_over(GameInfo_t *game_state);

#endif