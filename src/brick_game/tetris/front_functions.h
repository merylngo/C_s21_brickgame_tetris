#ifndef FRONT_H
#define FRONT_H

#include "free_game.h"
#include "init_game.h"
#include "main_header.h"
#include "moving.h"
#include "spawn.h"

void userInput(UserAction_t action, int hold);
BackGameInfo_t *updateCurrentState();

#endif