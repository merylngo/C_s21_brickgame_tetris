#include "main.h"

typedef enum {
  NORM,
  INCORRECT_MATRIX,  // Ошибка, некорректная матрица
  MEMORY_ERROR,
} matrix_memory_status;


int init_game(GameInfo_t *game_state);
matrix_memory_status create_field_matrix(GameInfo_t *game_state);