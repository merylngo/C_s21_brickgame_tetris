#include <ncurses.h>
#include <time.h>

#define FIELD_SIZE_Y 20
#define FIELD_SIZE_X 20
#define BORDER_LEFT 5
#define BORDER_UP 5
#define BORDER_RIGHT (BORDER_LEFT + FIELD_SIZE_X)
#define BORDER_BOTTOM (BORDER_UP + FIELD_SIZE_Y)
#define BLOCK_SIZE 4

enum fsm_states { START, SPAWN, MOVING, SHIFTING, ATTACHING, GAME_OVER };

enum block_codes { SQUARE };

typedef struct game_state_t {
  enum fsm_states state;
  int field_matrix[FIELD_SIZE_X][FIELD_SIZE_Y];
  enum block_codes current_block_code;
  int block_x, block_y;
} game_state_t;

void game_loop();

void init_game_state(game_state_t *game_state);

enum block_codes generate_next_block();

void print_field(game_state_t *game_state);
