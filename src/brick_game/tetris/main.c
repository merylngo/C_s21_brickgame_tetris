#include "main.h"

#include "gameplay.h"
#include "init_game.h"
#include "print_field.h"

int main(void) {
  initCli();

  playGame();

  endwin();

  return 0;
}

void initCli() {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  cbreak();
  // nodelay(stdscr, TRUE);
  timeout(200);
}

GameInfo_t *get_game_state() {
  static GameInfo_t game_state = {0};
  return &game_state;
}

void playGame() {
  GameInfo_t *game_state = get_game_state();
  current_block_t figure;
  // enum fsm_states fsm_status = START;

  get_memory_for_game(game_state);
  get_next_block(game_state);

  char command_code = 0;

  //int p = 40;

  do {
    init_current_block(game_state, &figure);

    get_next_block(game_state);

    // for (int i = 0; i < BLOCK_SIZE; i++) {
    //   for (int j = 0; j < BLOCK_SIZE; j++) {
    //     if (figure.matrix[i][j]) mvaddch(15 + i, p + j, '@');
    //   }
    // }

    // p += 10;

    do {
      print_matrix(&figure, game_state);

      // выполнение команды пользователя
      if ((command_code = getch()) && (command_code != 0)) {
        do_users_command(command_code, &figure, game_state);
      }

      // присоединение фигурки - фиксация на поле
      if (figure.y == FIELD_SIZE_Y ||
          game_state->field[figure.y][figure.x - 1] == 1) {
        game_state->field[figure.y - 1][figure.x - 1] = 1;
      }

      // падение фигуры на 1 шаг
      if (figure.y < FIELD_SIZE_Y) {
        (figure.y)++;
      }

      if (figure.y == FIELD_SIZE_Y ||
          game_state->field[figure.y][figure.x - 1] == 1) {
        game_state->field[figure.y - 1][figure.x - 1] = 1;
      }

      mvprintw(10, 40, "code = %d block: x = %d, y = %d\n\n", command_code,
               figure.x, figure.y);

    } while (able_to_move(&figure, game_state) && command_code != 27);

    // for (int i = 0; i < BLOCK_SIZE; i++) {
    //   for (int j = 0; j < BLOCK_SIZE; j++) {
    //     if (figure.matrix[i][j]) mvaddch(15 + i, p + j, '@');
    //   }
    // }

    // p += 10;

    remove_full_layers(game_state);

  } while (command_code != 27);

  remove_matrix(game_state->field, FIELD_SIZE_Y);
  remove_matrix(game_state->next_block, BLOCK_SIZE);
}