CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra -g
ASAN := -fsanitize=address
#directories
TETRIS_DIR_BACK := ./brick_game/tetris/

C_LIB_SRCS := $(wildcard $(TETRIS_DIR_BACK)/*.c)
C_LIB_OBJS := $(C_LIB_SRCS:%.c=%.o)

TETRIS_DIR_MAIN := ./gui/cli/
TESTS_DIR := ./tests

all: clean tetris

tetris_lib.a: $(C_LIB_OBJS)
	ar rcs ./$@ $^
	ranlib tetris_lib.a

$(TETRIS_DIR_MAIN)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

tetris: clean tetris_lib.a $(TETRIS_DIR_MAIN)*.c
	$(CC) $(CFLAGS) -o tetris -L. tetris_lib.a $(TETRIS_DIR_MAIN)*.c -lncurses 

build_test: clean tetris_lib.a $(TESTS_DIR)/*.c
	$(CC) $(CFLAGS) $(ASAN) $(TESTS_DIR)/*.c -o $(TESTS_DIR)/test.o -L. tetris_lib.a -lcheck -lsubunit -lm

test: build_test
	$(TESTS_DIR)/test.o

memcheck: clean build_test
	valgrind --tool=memcheck --leak-check=yes $(TESTS_DIR)/test.o

gcov_report: clean tetris_lib.a
	mkdir -p report
	$(CC) $(СFLAGS) --coverage -fprofile-arcs -ftest-coverage -L. tetris_lib.a $(TESTS_DIR)/*.c -o report/gcov_test -lm -lcheck -lgcov -lsubunit
	./report/gcov_test
	lcov -t "s21_test" -o report/s21_test.info -c -d report --ignore-errors mismatch,mismatch -o report/s21_test.info
	lcov -o report/s21_test.info -r report/s21_test.info "*/13/*"
	lcov -o report/s21_test.info -r report/s21_test.info "*/usr/include/*"
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
	@doxygen Doxyfile > /dev/null 2>&1
	@cd dvi/latex && latex -silent refman.tex > /dev/null 2>&1
	mv dvi/latex/refman.dvi dvi/
	rm -rf dvi/latex

run_dvi: dvi
	xdvi dvi/refman.dvi

dist:
	rm -rf dist/
	mkdir -p dist
	tar cvzf dist/BrickGame_1.0.tgz brick_game gui test FSM_tetris.jpeg Doxyfile Makefile mainpage.dox	

play: install
	./install/tetris	

clean:
	rm -rf tetris tetris_lib.a tetris.dSYM
	rm -rf $(TETRIS_DIR_BACK)/*.o $(TETRIS_DIR_MAIN)/*.o $(TESTS_DIR)/*.o
	rm -rf *.gcno *.gcda *.info report.out *.gcov report

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