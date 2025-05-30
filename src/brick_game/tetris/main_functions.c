#include "main_header.h"

BackGameInfo_t *get_game_state() {
  static BackGameInfo_t game_state = {0};
  return &game_state;
}