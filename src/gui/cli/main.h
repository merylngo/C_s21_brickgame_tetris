#ifndef S21_MAIN_H
#define S21_MAIN_H

#include <ncurses.h>
#include <time.h>

#include "../../brick_game/tetris/free_game.h"
#include "../../brick_game/tetris/main_header.h"
#include "print_screen.h"

#define START_TIMEOUT 400
#define START_KEY '\n'
#define FINISH_KEY 27

void init_cli();
void play_game();

void remove_matrix_info(int **matrix, int rows);
void free_game_info(GameInfo_t game_info);

UserAction_t get_action(int command);
int game_not_over(const BackGameInfo_t *game_state);

#endif