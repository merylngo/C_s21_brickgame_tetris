#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#define BLOCK_SIZE 4
#define FIELD_SIZE_Y 20
#define FIELD_SIZE_X 10
#define BORDER_LEFT 10
#define BORDER_UP 10
#define BORDER_RIGHT (BORDER_LEFT + FIELD_SIZE_X)
#define BORDER_BOTTOM (BORDER_UP + FIELD_SIZE_Y)

#include <stdlib.h>

enum fsm_states { START, SPAWN, MOVING, SHIFTING, ATTACHING, GAME_OVER };

typedef enum { RED = 1, GREEN, WHITE, YELLOW, BLUE } color_codes;

enum block_codes {
  SQUARE,
  LINE,
  LEFT_ANGLE,
  RIGHT_ANGLE,
  ZET,
  TURNED_ZET,
  TURNED_T
};

typedef struct {
  int **matrix;
  int x, y;
  color_codes color;
} current_block_t;

typedef struct {
  current_block_t figure;
  enum fsm_states fsm_state;
  int **field;
  int **next_block;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} BackGameInfo_t;  // GameInfo_t

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Down,
  Action
} UserAction_t;

BackGameInfo_t *get_game_state();

void copy_top_layers(int layer_number);
void remove_full_layers();
void attach_block();

int achieved_top_layer();
int achieved_max_level();
int game_is_over();

#endif
