CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra -g
ASAN := -fsanitize=address
#directories
TETRIS_DIR_BACK := ./brick_game/tetris/
TETRIS_DIR_MAIN := ./gui/cli/
TESTS_DIR := ./tests
#files
C_LIB_SRCS := $(wildcard $(TETRIS_DIR_BACK)/*.c)
C_LIB_OBJS := $(C_LIB_SRCS:%.c=%.o)
C_MAIN_SRCS := $(wildcard $(TETRIS_DIR_MAIN)/*.c)
C_MAIN_OBJS := $(C_MAIN_SRCS:%.c=%.o)


all: clean tetris

tetris_lib.a: $(C_LIB_OBJS)
	ar rcs ./$@ $^
	ranlib $@

$(TETRIS_DIR_BACK)%.o: $(TETRIS_DIR_BACK)%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Правило для компиляции объектных файлов из исходных файлов главного приложения
$(TETRIS_DIR_MAIN)%.o: $(TETRIS_DIR_MAIN)%.c
	$(CC) $(CFLAGS) -c $< -o $@

tetris: $(C_MAIN_OBJS) $(C_LIB_OBJS)
	$(CC) $(CFLAGS) -o tetris $(C_MAIN_OBJS) $(C_LIB_OBJS) -lncurses	

#tetris: clean $(TETRIS_DIR_MAIN)*.c $(TETRIS_DIR_BACK)*.c
#	$(CC) $(CFLAGS) -o tetris $(TETRIS_DIR_MAIN)*.c $(TETRIS_DIR_BACK)*.c -lncurses

build_test: clean tetris_lib.a $(TESTS_DIR)/*.c
	$(CC) $(CFLAGS) $(ASAN) $(TESTS_DIR)/*.c -o $(TESTS_DIR)/test -lcheck -lsubunit -lm

test: build_test
	$(TESTS_DIR)/test

memcheck: clean build_test
	valgrind --tool=memcheck --leak-check=yes $(TESTS_DIR)/test.o

gcov_report: clean
	mkdir -p report
	$(CC) $(СFLAGS) --coverage -fprofile-arcs -ftest-coverage $(TETRIS_DIR_BACK)*.c  $(TESTS_DIR)/*.c -o report/gcov_test -lcheck -lgcov -lsubunit -lm
	./report/gcov_test
	lcov -t "s21_test" -o report/s21_test.info -c -d report --ignore-errors mismatch,mismatch -o report/s21_test.info
	genhtml -o report report/s21_test.info
	xdg-open report/index.html

install: clean tetris
	rm -rf install
	mkdir -p install
	mv tetris ./install
	make clean

uninstall:
	-rm -rf install

dvi:
	@doxygen ./documentation/Doxyfile > /dev/null 2>&1
	@cd dvi/latex && latex -silent refman.tex > /dev/null 2>&1
	mv dvi/latex/refman.dvi dvi/
	rm -rf dvi/latex

run_dvi: dvi
	xdvi dvi/refman.dvi

dist:
	rm -rf dist/
	mkdir -p dist
	tar cvzf dist/BrickGame_Tetris.tgz Makefile brick_game gui tests documentation

play: install
	./install/tetris	

clean:
	rm -rf tetris tetris_lib.a tetris.dSYM dist
	rm -rf $(TETRIS_DIR_BACK)/*.o $(TETRIS_DIR_MAIN)/*.o $(TESTS_DIR)/*.o
	rm -rf *.gcno *.gcda *.info report.out *.gcov report

style:
	cp ../materials/linters/.clang-format ../src/
	clang-format -i $(TETRIS_DIR_BACK)*.h $(TETRIS_DIR_BACK)*.c
	clang-format -i $(TETRIS_DIR_MAIN)*.h $(TETRIS_DIR_MAIN)*.c
	clang-format -i $(TESTS_DIR)/*.c $(TESTS_DIR)/*.h

check:
	cp ../materials/linters/.clang-format ../src/
	clang-format -n $(TETRIS_DIR_BACK)*.h $(TETRIS_DIR_BACK)*.c
	clang-format -n $(TETRIS_DIR_MAIN)*.h $(TETRIS_DIR_MAIN)*.c
	clang-format -n $(TESTS_DIR)/*.c $(TESTS_DIR)/*.h