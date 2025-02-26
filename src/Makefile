CC := gcc
CFLAGS :=  -std=c11 -Wall -Werror -Wextra

all: clean tetris

tetris: main.c
	$(CC) $(CFLAGS) -o tetris main.c -lncurses

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
