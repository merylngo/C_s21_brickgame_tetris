#include "main.h"

#include "../../brick_game/tetris/free_game.h"
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
  int start_key;
  int flag_terminate_before = 0;

  while ((start_key = getch()) &&
         (start_key != START_KEY && start_key != FINISH_KEY)) {
    print_start_screen();
  }

  if (start_key == START_KEY) {
    userInput(Start, false);
  } else {
    userInput(Terminate, false);
    flag_terminate_before = 1;
  }

  const BackGameInfo_t *game_state = updateCurrentState();
  int delay = START_TIMEOUT;

  while (game_not_over(game_state)) {
    timeout(delay);

    if (game_state->pause) {
      print_pause_screen(*game_state);
      int command = getch();
      UserAction_t action = get_action(command);

      if (action == Pause || action == Terminate) {
        userInput(action, false);
      }
    } else {
      int command = getch();
      UserAction_t action = get_action(command);

      userInput(action, false);

      game_state = updateCurrentState();

      delay = START_TIMEOUT - 45 * game_state->speed;

      print_current_state(*game_state);
    }
  }
  if (!flag_terminate_before) {
    int finish_key;

    while ((finish_key = getch()) && finish_key != FINISH_KEY) {
      print_final_screen(*game_state);
    }

    free_game();
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

int game_not_over(const BackGameInfo_t *game_state) {
  return game_state->fsm_state != GAME_OVER;
}