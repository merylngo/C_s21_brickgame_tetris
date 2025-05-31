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

void init_cli();
void play_game();

UserAction_t get_action(int command);
int game_not_over(BackGameInfo_t *game_state);

#endif