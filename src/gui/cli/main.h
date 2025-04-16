#ifndef S21_MAIN_H
#define S21_MAIN_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define FIELD_SIZE_Y 20
#define FIELD_SIZE_X 10
#define BORDER_LEFT 5
#define BORDER_UP 5
#define BORDER_RIGHT (BORDER_LEFT + FIELD_SIZE_X)
#define BORDER_BOTTOM (BORDER_UP + FIELD_SIZE_Y)
#define BLOCK_SIZE 4

enum fsm_states { START, SPAWN, MOVING, SHIFTING, ATTACHING, GAME_OVER };

typedef enum {
  MOVE_DOWN,
  MOVE_RIGHT,
  MOVE_LEFT,
  ESCAPE,
  ENTER,
  PAUSE,
  END
} commands;

enum block_codes {
  SQUARE,
  LINE,
  LEFT_ANGLE,
  RIGHT_ANGLE,
  ZET,
  TURNED_ZET,
  TURNED_T
};

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

typedef enum { RED = 1, GREEN, WHITE, YELLOW, BLUE } color_codes;

typedef struct {
  int **field;
  int **next_block;
  int score;
  // int high_score;
  int level;
  // int speed;
  // int pause;
} GameInfo_t;

typedef struct {
  int **matrix;
  int x, y;
  color_codes color;
} current_block_t;

void init_cli();
void play_game();

GameInfo_t *get_game_state();

// GameInfo_t updateCurrentState();

#endif