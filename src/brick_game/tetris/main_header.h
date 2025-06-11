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

/**
 * @brief Состояния конечного автомата
 */

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
 * @brief Структура, описывающая текущую падающую фигурку, ее координаты на поле
 * и цвет
 */

typedef struct {
  int **matrix;
  int x, y;
  color_codes color;
} current_block_t;

/**
 * @brief Основная структура, описывающая полное состояние игры
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
} BackGameInfo_t;  // GameInfo_t

/**
 * @brief Действия пользователя
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
 * @brief Функция userInput(UserAction_t action, int hold)
 *
 * Интерпретирует команду пользователя в действие в игре и изменяет ее состояние
 *
 * @param action - действие пользователя
 * @param hold - не используется
 */
void userInput(UserAction_t action, int hold);

/**
 * @brief Функция updateCurrentState()
 *
 * возвращает в игровой цикл константный указатель на статическую переменную,
 * описывающую текущее состояние игры
 *
 * @return const BackGameInfo_t *
 */
const BackGameInfo_t *updateCurrentState();

/**
 * @brief Функция get_game_state()
 *
 * возвращает указатель на статическую переменную, описывающую текущее состояние
 * игры
 *
 * @return BackGameInfo_t *
 */
BackGameInfo_t *get_game_state();

#endif