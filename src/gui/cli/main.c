#include "main.h"

#include "../../brick_game/tetris/main_header.h"

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
  init_colors();
  nodelay(stdscr, TRUE);
}

void play_game() {
  int game_status = PLAYING_STATUS;

    int start_key;

    while ((start_key = getch()) &&
           (start_key != START_KEY && start_key != FINISH_KEY)) {
      print_start_screen();
    }

    if (start_key == START_KEY) {
      userInput(Start, false);
    } else {
      userInput(Terminate, false);
      game_status = GAMEOVER_STATUS;
    }

    GameInfo_t game_info = {0};
    int delay = START_TIMEOUT;

    while (game_status != GAMEOVER_STATUS) {
      timeout(delay);

      game_info = updateCurrentState();
      game_status = game_info.pause;

      if (game_status == PAUSE_STATUS) {
        print_pause_screen(game_info);

        int command = getch();
        UserAction_t action = get_action(command);

        if (action == Pause || action == Terminate) {
          userInput(action, false);
        }
      } else if (game_status == PLAYING_STATUS) {
        print_current_state(game_info);
        delay = START_TIMEOUT - 45 * game_info.speed;

        int command = getch();
        UserAction_t action = get_action(command);

        userInput(action, false);
      }

      if (game_status == GAMEOVER_STATUS) {
        int finish_key;

        while ((finish_key = getch()) &&
               (finish_key != FINISH_KEY)) {
          print_final_screen(game_info);
        }
      }

      free_game_info(game_info);
    }
}

UserAction_t get_action(int command) {
  UserAction_t action = 0;

  switch (command) {
    case 'p':
      action = Pause;
      break;
    case 'q':
      action = Terminate;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_UP:
      action = Action;
      break;
    case 32:
      action = Down;
      break;

    default:
      action = Empty;
      break;
  }

  return action;
}

void remove_matrix_info(int **matrix, int rows) {
  if (matrix) {
    for (int i = 0; i < rows; i++) {
      if (matrix[i]) {
        free(matrix[i]);
      }
    }

    free(matrix);
  }

  matrix = NULL;
}

void free_game_info(GameInfo_t game_info) {
  remove_matrix_info(game_info.field, FIELD_SIZE_Y);
  remove_matrix_info(game_info.next, BLOCK_SIZE);
}