CC := gcc
CFLAGS :=  -std=c11 -Wall -Werror -Wextra
TETRIS_DIR := ./brick_game/tetris/

all: clean tetris

tetris: $(TETRIS_DIR)main.c
	$(CC) $(CFLAGS) -o tetris  $(TETRIS_DIR)main.c -lncurses

clean:
	rm -rf tetris	

style:
	cp ../materials/linters/.clang-format ../src/
	clang-format -i *.c
	clang-format -i *.h
	clang-format -i tests/*.c
	clang-format -i tests/*.h

check:
	cp ../materials/linters/.clang-format ../src/
	clang-format -n *.c
	clang-format -n *.h
	clang-format -n tests/*.c
	clang-format -n tests/*.h
