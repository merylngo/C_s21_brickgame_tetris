/**
 * @file main_header.h
 * @brief Header file for the all game
 *
 */

#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#define BLOCK_SIZE 4
#define FIELD_SIZE_Y 20
#define FIELD_SIZE_X 10
#define BORDER_LEFT 10
#define BORDER_UP 10
#define BORDER_RIGHT (BORDER_LEFT + FIELD_SIZE_X)
#define BORDER_BOTTOM (BORDER_UP + FIELD_SIZE_Y)

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  START,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAME_OVER
} fsm_states;

typedef enum { RED = 1, GREEN, YELLOW, BLUE, PINK, PURPLE, WHITE } color_codes;

enum block_codes {
  SQUARE,
  LINE,
  LEFT_ANGLE,
  RIGHT_ANGLE,
  ZET,
  TURNED_ZET,
  TURNED_T
};

/**
 * @brief Current block struct
 */
typedef struct {
  int **matrix;
  int x, y;
  color_codes color;
} current_block_t;

/**
 * @brief all static game information in backend
 */
typedef struct {
  fsm_states fsm_state;
  current_block_t figure;
  int **field;
  int **next_block;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} BackGameInfo_t;

/**
 * @brief struct for frontend to show in interface
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief User's actions
 */

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Down,
  Action,
  Empty
} UserAction_t;

/**
 * @brief Function userInput(UserAction_t action, int hold)
 *
 */
void userInput(UserAction_t action, int hold);

/**
 * @brief Function update_current_state()

 *
 * @return const BackGameInfo_t *
 */
const BackGameInfo_t *update_current_state();

/**
 * @brief Function updateCurrentState()

 *
 * @return const BackGameInfo_t *
 */
GameInfo_t updateCurrentState();

/**
 * @brief Function get_game_state()

 *
 * @return BackGameInfo_t *
 */
BackGameInfo_t *get_game_state();

#endif