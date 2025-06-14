#ifndef S21_MAIN_H
#define S21_MAIN_H

#include <ncurses.h>
#include <time.h>

#include "../../brick_game/tetris/main_header.h"
#include "print_screen.h"

#define START_TIMEOUT 300
#define DELAY_MUL 20
#define START_KEY '\n'
#define FINISH_KEY 27
#define PLAYING_STATUS 0
#define PAUSE_STATUS 1
#define GAMEOVER_STATUS 2
#define EXIT_STATUS 3
#define NEW_GAME_STATUS 4

void init_cli();
void play_game();

UserAction_t get_action(int command);

void on_start_state(int *game_status);
void on_pause_state(GameInfo_t game_info);
void on_playing_state(GameInfo_t game_info, int *delay, clock_t *start_time);
void on_game_over_state(int *game_status, GameInfo_t game_info);

void remove_matrix_info(int **matrix, int rows);
void free_game_info(GameInfo_t game_info);

#endif