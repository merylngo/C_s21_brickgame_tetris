#include "print_field.h"

void init_colors() {
  start_color();
  init_pair(RED, COLOR_RED, COLOR_RED);
  init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
  init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
}

void print_matrix(current_block_t *figure, GameInfo_t *game_state) {
  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (game_state->field[i][j]) {
        // mvaddch(i, j * 2, '#');
        // mvaddch(i, j * 2 + 1, '#');

        print_cell(game_state->field[i][j], i, j * 2, '#');
        print_cell(game_state->field[i][j], i, j * 2 + 1, '#');
      } else {
        // mvaddch(i, j * 2, '-');
        // mvaddch(i, j * 2 + 1, '-');

        print_cell(0, i, j * 2, '-');
        print_cell(0, i, j * 2 + 1, '-');
      }
    }

    // printw("%d", i);
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++)
      if (figure->matrix[i][j]) {
        // mvaddch(figure->y + i, (figure->x + j) * 2, '[');
        // mvaddch(figure->y + i, (figure->x + j) * 2 + 1, ']');

        print_cell(figure->color, figure->y + i, (figure->x + j) * 2, '[');
        print_cell(figure->color, figure->y + i, (figure->x + j) * 2 + 1, ']');
      }
  }
}

void print_cell(int color_code, int x, int y, char sign) {
  if (color_code) {
    attron(COLOR_PAIR(color_code));

    mvaddch(x, y, sign);

    attroff(COLOR_PAIR(color_code));
  } else {
    mvaddch(x, y, sign);
  }
}

void show_start_screen() {
  mvprintw(10, 10, "Press ENTER button to start\nPress any other key to end\n");
}