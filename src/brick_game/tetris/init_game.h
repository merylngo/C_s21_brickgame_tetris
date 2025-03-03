#include "main.h"

enum matrix_memory_status {
  NORM,
  INCORRECT_MATRIX,  // Ошибка, некорректная матрица
  MEMORY_ERROR,
};


int init_game(GameInfo_t *game_state);
enum matrix_memory_status create_field_matrix(GameInfo_t *game_state);