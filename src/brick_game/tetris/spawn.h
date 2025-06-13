/**
 * @file spawn.h
 * @brief Header file for spawn logic
 *
 */

#ifndef BLOCKS_H
#define BLOCKS_H

#include "main_header.h"

void copy_matrix(int src[][BLOCK_SIZE], int ***dest);
void copy_matrix_pt(int **src, int ***dest);
void init_current_block();
enum block_codes generate_next_block();
color_codes generate_color_code();
void get_block(enum block_codes block_code, int ***block);
void get_next_block();

void spawn_block();

#endif