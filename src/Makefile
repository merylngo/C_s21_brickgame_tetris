CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra -g
TETRIS_DIR_BACK := ./brick_game/tetris/
TETRIS_DIR_MAIN := ./gui/cli/
TESTS_DIR := ./tests
OBJ_DIR := ./obj
C_SRCS := $(wildcard $(TETRIS_DIR_MAIN)/*.c $(TETRIS_DIR_BACK)/*.c)
C_OBJS := $(C_SRCS:%.c=%.o)
C_SRCS_TEST := $(wildcard $(TETRIS_DIR_BACK)/*.c)
C_OBJS_TEST := $(C_SRCS_TEST:%.c=%.o)
ASAN=-g -fsanitize=address


all: clean tetris

tetris: $(TETRIS_DIR_BACK)*.c $(TETRIS_DIR_MAIN)*.c
	$(CC) $(CFLAGS) -o tetris  $(TETRIS_DIR_BACK)*.c $(TETRIS_DIR_MAIN)*.c -lncurses 

tetris_lib.a: $(C_OBJS_TEST)
	ar rcs ./$@ $^
	ranlib tetris_lib.a

test: clean tetris_lib.a $(TESTS_DIR)/*.c
	$(CC) $(CFLAGS) $(ASAN) $(TESTS_DIR)/*.c -o $(TESTS_DIR)/test.o -L. tetris_lib.a -lcheck -lsubunit -lm
	$(TESTS_DIR)/test.o

clean:
	rm -rf tetris tetris_lib.a
	rm -rf $(TETRIS_DIR_BACK)/*.o	
	rm -rf $(TESTS_DIR)/*.o	

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