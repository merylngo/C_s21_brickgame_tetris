#ifndef FRONT_H
#define FRONT_H

#include "init_game.h"
#include "main_header.h"
#include "moving.h"

void userInput(UserAction_t action, int hold);
GameInfo_t updateCurrentState();

#endif