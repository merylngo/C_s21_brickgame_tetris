#ifndef FRONT_H
#define FRONT_H

#include "../../gui/cli/main.h"
#include "gameplay.h"

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif