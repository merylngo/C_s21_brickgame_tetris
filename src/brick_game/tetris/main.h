#include <ncurses.h>
#include <time.h>

#define FIELD_SIZE_Y 20
#define FIELD_SIZE_X 20
#define BLOCK_SIZE 4

enum fsm_states {
    START,
    SPAWN,
    MOVING,
    SHIFTING,
    ATTACHING,
    GAME_OVER
};

typedef struct game_state_t
{
  fsm_states state;
  int field_matrix[FIELD_SIZE_X][FIELD_SIZE_Y];
  int current_block_code;
  int block_x, block_y;
} game_state_t;

void game_loop();

void init_field(char field[FIELD_SIZE_X + 2][FIELD_SIZE_Y + 2]);
void print_field_with_x_y(char field[FIELD_SIZE_X + 2][FIELD_SIZE_Y + 2], int y,
                          int x);
