#include "main.h"

#include "../../brick_game/tetris/gameplay.h"
#include "../../brick_game/tetris/init_game.h"
#include "print_field.h"

int main(void) {
  init_cli();
  play_game();
  endwin();

  return 0;
}

void init_cli() {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  cbreak();
  // nodelay(stdscr, TRUE);
  timeout(300);
}

#if 0

void init_game();


void init_game()
{
    get_memory_for_game(game_state);
    get_next_block(game_state);
}

int game_over();

void play_game() {
  GameInfo_t *game_state = get_game_state();
  current_block_t figure;

  for (;;) {
    show_start_screen();
    char key;

    if (key != 'ENTER') {
      break;
    }

    init_game();

    while (!game_over()) {

      // SPAWN
      
      init_current_block(game_state, &figure);
      get_next_block(game_state);

      // MOVING + SHIFTING

      do {
        char command = getch();
        UserAction_t action;

        switch (command) {
          case 's':
            action = Start;
            break;
          case 'p':
            action = Pause;
            break;
          case 'KEY_LEFT':  
            action = Left;
            break;
          case 'KEY_RIGHT':
            action = Right;
            break;
          case 'KEY_DOWN':
            action = Down;
            break;
          case 'KEY_UP':
            action = Action;
            break;

          default:
            break;
        }

        UserInput(action, false);
        *game_state = UpdateCurrentState();
        print_matrix(&figure, game_state);
      } while (able_to_move_down(&figure, game_state))

      // ATTACHING

      attach_block_on_field(&figure, game_state);
      remove_full_layers(game_state);

      *game_state = UpdateCurrentState();
      print_matrix(&figure, game_state);
    }

    remove_matrix(game_state->field, FIELD_SIZE_Y);
    remove_matrix(game_state->next_block, BLOCK_SIZE);
  }


  return 0;
}

#endif

GameInfo_t *get_game_state() {
  static GameInfo_t game_state = {0};
  return &game_state;
}

void play_game() {
  GameInfo_t *game_state = get_game_state();
  current_block_t figure;
  char command_code = 0;
  int flag = 0;
  // enum fsm_states fsm_status = START;

  get_memory_for_game(game_state);
  get_next_block(game_state);

  do {
    init_current_block(game_state, &figure);

    get_next_block(game_state);

    do {
      print_matrix(&figure, game_state);

      flag = able_to_move_down(&figure, game_state);

      if (flag && (command_code = getch()) && (command_code != 0)) {
        do_users_command(command_code, &figure, game_state);
      }

      flag = able_to_move_down(&figure, game_state);

      if (flag) {
        move_down(&figure);
      } /* else {
        attach_block_on_field(&figure, game_state);
      } */

      mvprintw(9, 40, "flag = %d\n", flag);
      mvprintw(10, 40, "code = %d block: x = %d, y = %d\n\n", command_code,
               figure.x, figure.y);

    } while (flag && command_code != 27 && game_is_over(&figure, game_state));

    attach_block_on_field(&figure, game_state);
    remove_full_layers(game_state);

  } while (command_code != 27 && game_is_over(&figure, game_state));

  remove_matrix(game_state->field, FIELD_SIZE_Y);
  remove_matrix(game_state->next_block, BLOCK_SIZE);
}