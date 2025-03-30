CC := gcc
CFLAGS :=  -std=c11 -Wall -Werror -Wextra
TETRIS_DIR_BACK := ./brick_game/tetris/
TETRIS_DIR_MAIN := ./gui/cli/

all: clean tetris

tetris: $(TETRIS_DIR_BACK)*.c $(TETRIS_DIR_MAIN)*.c
	$(CC) $(CFLAGS) -o tetris  $(TETRIS_DIR_BACK)*.c $(TETRIS_DIR_MAIN)*.c -lncurses 
	
# -g -fsanitize=address

clean:
	rm -rf tetris	

style:
	cp ../materials/linters/.clang-format ../src/
	clang-format -i $(TETRIS_DIR_MAIN)*.c $(TETRIS_DIR_BACK)*.c
	clang-format -i $(TETRIS_DIR_MAIN)*.h $(TETRIS_DIR_BACK)*.h

check:
	cp ../materials/linters/.clang-format ../src/
	clang-format -n *.c
	clang-format -n *.h
