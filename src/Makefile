CC := gcc
CFLAGS :=  -std=c11 -Wall -Werror -Wextra -g
TETRIS_DIR_BACK := ./brick_game/tetris/
TETRIS_DIR_MAIN := ./gui/cli/
TESTS_DIR := ./tests
OBJ_DIR := ./obj
C_SRCS := $(wildcard $(TETRIS_DIR_MAIN)/*.c $(TETRIS_DIR_BACK)/*.c)
C_OBJS := $(C_SRCS:%.c=%.o)


all: clean tetris

tetris: $(TETRIS_DIR_BACK)*.c $(TETRIS_DIR_MAIN)*.c
	$(CC) $(CFLAGS) -o tetris  $(TETRIS_DIR_BACK)*.c $(TETRIS_DIR_MAIN)*.c -lncurses 

clean:
	rm -rf tetris	

style:
	cp ../materials/linters/.clang-format ../src/
	clang-format -i $(TETRIS_DIR_MAIN)*.c $(TETRIS_DIR_BACK)*.c
	clang-format -i $(TETRIS_DIR_MAIN)*.h $(TETRIS_DIR_BACK)*.h
	clang-format -i $(TESTS_DIR)/*.c
	clang-format -i $(TESTS_DIR)/*.h


check:
	cp ../materials/linters/.clang-format ../src/
	clang-format -n *.c
	clang-format -n *.h
	clang-format -n $(TESTS_DIR)/*.c
	clang-format -n $(TESTS_DIR)/*.h


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)