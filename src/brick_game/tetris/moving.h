#ifndef MOVING_H
#define MOVING_H

#include "main_header.h"

void move_left();
int able_to_move_left();

void move_right();
int able_to_move_right();

void move_down();
void fall_down();
int able_to_move_down();

void normalize_matrix(int matrix[][BLOCK_SIZE]);
void turn_left_matrix();
int able_to_turn_left();
void turn_left();

void move_block(UserAction_t action);

#endif