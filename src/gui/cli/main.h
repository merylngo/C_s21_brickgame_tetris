#ifndef S21_MAIN_H
#define S21_MAIN_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../../brick_game/tetris/front_functions.h"
#include "../../brick_game/tetris/init_game.h"
#include "print_screen.h"

#define FIELD_SIZE_Y 20
#define FIELD_SIZE_X 10
#define BORDER_LEFT 10
#define BORDER_UP 10
#define BORDER_RIGHT (BORDER_LEFT + FIELD_SIZE_X)
#define BORDER_BOTTOM (BORDER_UP + FIELD_SIZE_Y)
#define BLOCK_SIZE 4

typedef enum {
  MOVE_DOWN,
  MOVE_RIGHT,
  MOVE_LEFT,
  ESCAPE,
  ENTER,
  PAUSE,
  END
} commands;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next_block;
  int score;
  // int high_score;
  int level;
  // int speed;
  // int pause;
} GameInfo_t;

typedef enum { RED = 1, GREEN, WHITE, YELLOW, BLUE } color_codes;

void init_cli();
void play_game();

int game_not_over(GameInfo_t *game_state);

UserAction_t get_action(char command);

#endif