#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "../../gui/cli/main.h"

enum fsm_states { START, SPAWN, MOVING, SHIFTING, ATTACHING, GAME_OVER };

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
  enum fsm_states current_state;
  int **field;
  int **next_block;
  int score;
  // int high_score;
  int level;
  // int speed;
  // int pause;
} BackGameInfo_t;

typedef struct {
  int **field;
  int **next_block;
  int score;
  // int high_score;
  int level;
  // int speed;
  // int pause;
} GameInfo_t;

BackGameInfo_t *get_game_state();

void normalize_matrix(current_block_t *figure);
void turn_left_matrix(current_block_t *figure);
void move_left(current_block_t *figure);
void move_right(current_block_t *figure);
void move_down(current_block_t *figure);
void fall_down(current_block_t *figure, GameInfo_t *game_state);

int able_to_turn(current_block_t *figure, GameInfo_t *game_state);
int able_to_move_left(current_block_t *figure, GameInfo_t *game_state);
int able_to_move_right(current_block_t *figure, GameInfo_t *game_state);
int able_to_move_down(current_block_t *figure, GameInfo_t *game_state);

void do_users_command(int command_code, current_block_t *figure,
                      GameInfo_t *game_state);

void attach_block_on_field(current_block_t *figure, GameInfo_t *game_state);

void copy_top_layers(int layer_number, GameInfo_t *game_state);
void remove_full_layers(GameInfo_t *game_state);

void init_current_block(GameInfo_t *game_state, current_block_t *figure);

void copy_matrix(int src[][BLOCK_SIZE], int **dest);
enum block_codes generate_next_block();
color_codes generate_color_code();
void get_block(enum block_codes block_code, int **block);
void get_next_block(GameInfo_t *game_state);

int game_is_over(current_block_t *figure, GameInfo_t *game_state);

#endif