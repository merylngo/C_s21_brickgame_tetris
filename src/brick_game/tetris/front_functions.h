#ifndef FRONT_H
#define FRONT_H

#include "blocks.h"
#include "free_game.h"
#include "init_game.h"
#include "main_header.h"
#include "moving.h"

void userInput(UserAction_t action, int hold);
BackGameInfo_t updateCurrentState();

#endif