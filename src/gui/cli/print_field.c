#include "print_field.h"

void init_colors() {
  start_color();
  init_pair(RED, COLOR_RED, COLOR_RED);
  init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
  init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
}

void print_cell(int color_code, int x, int y, char sign) {
  if (color_code) {
    attron(COLOR_PAIR(color_code));

    mvaddch(BORDER_LEFT + x, BORDER_UP + y, sign);

    attroff(COLOR_PAIR(color_code));
  } else {
    mvaddch(BORDER_LEFT + x, BORDER_UP + y, sign);
  }
}

void print_matrix(current_block_t *figure) {
  GameInfo_t *game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (game_state->field[i][j]) {
        print_cell(game_state->field[i][j], i, j * 2, '[');
        print_cell(game_state->field[i][j], i, j * 2 + 1, ']');
      } else {
        print_cell(0, i, j * 2, '-');
        print_cell(0, i, j * 2 + 1, '-');
      }
    }

    // printw("%d", i);
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++)
      if (figure->matrix[i][j]) {
        print_cell(figure->color, figure->y + i, (figure->x + j) * 2, '[');
        print_cell(figure->color, figure->y + i, (figure->x + j) * 2 + 1, ']');
      }
  }
}

void print_info_screen() {
  GameInfo_t *game_state = get_game_state();

  mvprintw(BORDER_UP, BORDER_RIGHT * 2, "info:");
  mvprintw(BORDER_UP + 1, BORDER_RIGHT * 2, "score: %d", game_state->score);
  mvprintw(BORDER_UP + 2, BORDER_RIGHT * 2, "next_block:");

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (game_state->next_block[i][j]) {
        mvaddch(BORDER_UP + 3 + i, BORDER_RIGHT * 2 + j, '[');
        mvaddch(BORDER_UP + 3 + i, BORDER_RIGHT * 2 + j + 1, ']');
      }
    }
  }
}

void print_start_screen() {
  mvprintw(10, 10, "Press ENTER button to start\n");
  mvprintw(11, 10, "Press any other key to end\n");
}

void print_pause_screen() {
  GameInfo_t *game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (game_state->field[i][j]) {
        print_cell(0, i, j * 2, '[');
        print_cell(0, i, j * 2 + 1, ']');
      } else {
        print_cell(0, i, j * 2, '-');
        print_cell(0, i, j * 2 + 1, '-');
      }
    }
  }
}

void print_final_screen() {
  GameInfo_t *game_state = get_game_state();

  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (game_state->field[i][j]) {
        print_cell(0, i, j * 2, '[');
        print_cell(0, i, j * 2 + 1, ']');
      } else {
        print_cell(0, i, j * 2, '-');
        print_cell(0, i, j * 2 + 1, '-');
      }
    }
  }
}