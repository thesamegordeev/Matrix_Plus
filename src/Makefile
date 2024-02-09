GCCFLAGS= --std=c++17 -lstdc++ -lm
WFLAGS=-Wall -Werror -Wextra
GTESTFLAGS= -lgtest

all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	@gcc -c $(GCCFLAGS) $(WFLAGS) s21_matrix_oop.cc -o s21_matrix_oop.o 
	@ar rcs s21_matrix_oop.a s21_matrix_oop.o
	@ranlib s21_matrix_oop.a
	@rm s21_matrix_oop.o

test: s21_matrix_oop.a
	@gcc s21_matrix_oop_tests.cc s21_matrix_oop.a $(GTESTFLAGS) $(GCCFLAGS) -o test
	@./test

clean:
	@rm -rf report* test* s21_matrix_oop.o s21_matrix_oop.a *.info *.gc* .clang-format

gcov_report:
	@gcc s21_matrix_oop_tests.cc s21_matrix_oop.cc --coverage $(GTESTFLAGS) $(GCCFLAGS) -o test
	@./test
	@lcov -t test -o s21_test.info -c -d .
	@lcov -e s21_test.info '/home/thesamegordeev/CPP1_s21_matrixplus-1/src/s21_matrix_oop.cc' -o report.info
	@genhtml -o report report.info
	@open ./report/index.html

valgrind: s21_matrix_oop.a
	@gcc s21_matrix_oop_tests.cc s21_matrix_oop.a $(GTESTFLAGS) $(GCCFLAGS) -o test
	@valgrind --tool=memcheck --leak-check=yes ./test

style_check: 
	@cp ../materials/linters/.clang-format .
	clang-format -style=Google -n *.cc *.h
	@rm .clang-format