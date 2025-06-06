#ifndef S21_MAIN_H
#define S21_MAIN_H

#include <ncurses.h>
#include <time.h>

#include "../../brick_game/tetris/main_header.h"
#include "../../brick_game/tetris/front_functions.h"
#include "../../brick_game/tetris/free_game.h"
#include "print_screen.h"

#define START_TIMEOUT 400
#define START_KEY '\n'

void init_cli();
void play_game();

UserAction_t get_action(int command);
int game_not_over(BackGameInfo_t *game_state);

#endif