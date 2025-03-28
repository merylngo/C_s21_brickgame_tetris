CC := gcc
CFLAGS :=  -std=c11 -Wall -Werror -Wextra
TETRIS_DIR := ./brick_game/tetris/

all: clean tetris

tetris: $(TETRIS_DIR)*.c
	$(CC) $(CFLAGS) -o tetris  $(TETRIS_DIR)*.c -lncurses 
	
# -g -fsanitize=address

clean:
	rm -rf tetris	

style:
	cp ../materials/linters/.clang-format ../src/
	clang-format -i $(TETRIS_DIR)*.c
	clang-format -i $(TETRIS_DIR)*.h

check:
	cp ../materials/linters/.clang-format ../src/
	clang-format -n *.c
	clang-format -n *.h
