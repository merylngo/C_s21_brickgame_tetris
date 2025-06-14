/**
 * @file attaching.h
 * @brief Header file for the attaching logic of the Tetris game.
 *
 */

#ifndef ATTACHING_H
#define ATTACHING_H

void copy_top_layers(int layer_number);
void remove_full_layers();
int able_to_attach_block();
void attach_block();

void update_score(int cnt_layers);
void update_level();
void update_high_score();
int achieved_top_layer();
int achieved_max_level();
int game_is_over();

#endif