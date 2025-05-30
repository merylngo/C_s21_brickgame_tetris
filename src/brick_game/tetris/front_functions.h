#ifndef FRONT_H
#define FRONT_H

#include "main_header.h"
#include "gameplay.h"
#include "moving.h"

UserAction_t get_action(char command);
void userInput(UserAction_t action, int hold);
GameInfo_t updateCurrentState();

#endif