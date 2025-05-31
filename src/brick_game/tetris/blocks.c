#include "blocks.h"

void get_block(enum block_codes block_code, int **block) {
  if (block_code == SQUARE) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == LINE) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == RIGHT_ANGLE) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == LEFT_ANGLE) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == ZET) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == TURNED_ZET) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }

  if (block_code == TURNED_T) {
    int block_src[BLOCK_SIZE][BLOCK_SIZE] = {
        {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    copy_matrix(block_src, block);
  }
}

enum block_codes generate_next_block() {
  return (enum block_codes)(rand() % 7);
}

color_codes generate_color_code() { return (color_codes)(rand() % 5 + 1); }

void get_next_block() {
  BackGameInfo_t *game_state = get_game_state();

  get_block(generate_next_block(), game_state->next_block);
}

void init_current_block() {
  BackGameInfo_t *game_state = get_game_state();

  game_state->figure.matrix = game_state->next_block;

  game_state->figure.x = FIELD_SIZE_X / 2 - 1;
  game_state->figure.y = 0;

  game_state->figure.color = generate_color_code();
}

void spawn_block() {
  init_current_block();
  get_next_block();
}