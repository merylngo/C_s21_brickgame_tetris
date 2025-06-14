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

$(TETRIS_DIR_MAIN)%.o: $(TETRIS_DIR_MAIN)%.c
	$(CC) $(CFLAGS) -c $< -o $@

tetris: clean $(C_MAIN_OBJS) tetris_lib.a
	mkdir -p build
	$(CC) $(CFLAGS) -o ./build/tetris $(C_MAIN_OBJS) -L. tetris_lib.a -lncurses

build_test: clean tetris_lib.a $(TESTS_DIR)/*.c
	$(CC) $(CFLAGS) $(ASAN) $(TESTS_DIR)/*.c -o $(TESTS_DIR)/test -L. tetris_lib.a -lcheck -lsubunit -lm

test: build_test
	$(TESTS_DIR)/test

build_test_no_asan: clean tetris_lib.a $(TESTS_DIR)/*.c
	$(CC) $(CFLAGS) $(TESTS_DIR)/*.c -o $(TESTS_DIR)/test -L. tetris_lib.a -lcheck -lsubunit -lm

memcheck_back: clean build_test_no_asan
	valgrind --tool=memcheck --leak-check=yes $(TESTS_DIR)/test

gcov_report: clean
	mkdir -p report
	$(CC) $(CFLAGS) --coverage -fprofile-arcs -ftest-coverage $(TETRIS_DIR_BACK)*.c  $(TESTS_DIR)/*.c -o report/gcov_test -lcheck -lgcov -lsubunit -lm
	./report/gcov_test
	lcov -t "s21_test" -o report/s21_test.info -c -d report --ignore-errors mismatch,mismatch -o report/s21_test.info
	genhtml -o report report/s21_test.info
	xdg-open report/index.html

install: tetris
	rm -rf install
	mkdir -p install
	mv ./build/tetris ./install
	mv tetris_lib.a ./install

uninstall: clean
	-rm -rf install

# sudo apt install texlive-full
# sudo apt-get install doxygen

dvi: clean_dvi
	@doxygen ./documentation/Doxyfile > /dev/null 2>&1
	@mkdir -p dvi/latex
	@cd dvi/latex && latex refman.tex > /dev/null 2>&1
	@mv dvi/latex/refman.dvi ./documentation
	@rm -rf ./dvi

run_dvi: dvi
	xdvi ./documentation/refman.dvi		

clean_dvi:
	@rm ./documentation/refman.dvi

dist: clean
	rm -rf dist/
	mkdir -p dist
	tar cvzf dist/BrickGame_Tetris.tgz Makefile brick_game gui tests documentation

play: install
	./install/tetris	

clean:
	rm -rf ./build tetris_lib.a ./dist ./dvi
	rm -rf $(TETRIS_DIR_BACK)/*.o $(TETRIS_DIR_MAIN)/*.o $(TESTS_DIR)/*.o $(TESTS_DIR)/test
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