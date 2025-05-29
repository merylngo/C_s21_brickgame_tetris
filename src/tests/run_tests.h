#ifndef MAIN_H_
#define MAIN_H_

#include <check.h>
#include <limits.h>
#include <stdio.h>

#define GREEN_BCGR "\033[42m"
#define RED_BCGR "\033[31m"
#define YELLOW_BCGR "\033[43m \033[30m"
#define WHITE_FONT "\033[97m"
#define RESET_COLORS "\033[0m"

#define SIZE 100

Suite* create_remove_test(void);

#endif
