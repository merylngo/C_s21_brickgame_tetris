#include "print_field.h"

// void print_field(WINDOW *win, current_block_t *figure, GameInfo_t
// *game_state) {
//   for (int i = 0; i < FIELD_SIZE_Y; i++) {
//     for (int j = 0; j < FIELD_SIZE_X; j++) {
//       if ((figure->y == i + 1 && figure->x == j + 1) ||
//       (game_state->field[i][j] == 1 && game_state->field[i][j] == 0)) {
//         mvwaddch(win, i + 1, j + 1, '@');
//       } else {
//         mvwaddch(win, i + 1, j + 1, ' ');
//       }
//     }
//   }
// }

void print_matrix(current_block_t *figure, GameInfo_t *game_state) {
  for (int i = 0; i < FIELD_SIZE_Y; i++) {
    for (int j = 0; j < FIELD_SIZE_X; j++) {
      if (game_state->field[i][j] == 1) {
        mvaddch(i + 1, j + 1, '#');
      } else {
        mvaddch(i + 1, j + 1, '-');
      }

      if (figure->y == i + 1 && figure->x == j + 1) {
        mvaddch(i + 1, j + 1, '@');
      }
    }
  }
}