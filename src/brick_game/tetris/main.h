#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define FIELD_SIZE_Y 20
#define FIELD_SIZE_X 20
#define BORDER_LEFT 5
#define BORDER_UP 5
#define BORDER_RIGHT (BORDER_LEFT + FIELD_SIZE_X)
#define BORDER_BOTTOM (BORDER_UP + FIELD_SIZE_Y)
#define BLOCK_SIZE 4

enum fsm_states { START, SPAWN, MOVING, SHIFTING, ATTACHING, GAME_OVER };

enum matrix_memory_status {
  NORM,
  INCORRECT_MATRIX,  // Ошибка, некорректная матрица
  MEMORY_ERROR,
};

enum block_codes { SQUARE };

typedef struct game_state_t {
  enum fsm_states state;
  int field_matrix[FIELD_SIZE_X][FIELD_SIZE_Y];
  enum block_codes current_block_code;
  int block_x, block_y;
} game_state_t;

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
  int **next;
  // int score;
  // int high_score;
  // int level;
  // int speed;
  // int pause;
} GameInfo_t;

void game_loop();

void init_game_state(game_state_t *game_state);

void get_user_command(game_state_t *game_state);

enum block_codes generate_next_block();

void print_field(game_state_t *game_state);
