GCC = gcc 
FLAGS= -Wall -Wextra -Werror -std=c11
LIBNAME = s21_matrix

ifeq ($(shell uname), Darwin)
    TEST_FLAGS=-lcheck
else
    TEST_FLAGS=-lcheck -lsubunit -pthread -lrt -lm --coverage
endif

all: s21_matrix.a

clean:
	rm -rf *.o tests/*.o
	rm -rf *.a
	rm -rf tests/report
	rm -rf tests/test*
	rm -rf *.gcda *.gcno tests/*.gcda tests/*.gcno
	rm -rf main test test.info report
	
rebuild: clean s21_matrix.a

s21_matrix.a:
	$(GCC) $(FLAGS) -c s21_*.c
	ar cr $(LIBNAME).a s21_*.o
	ranlib $(LIBNAME).a

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

open:
	open report/index.html

test: clean $(TEST_FILE_NAME) s21_matrix.a
	gcc -std=c11 -Wall -Werror -Wextra -g s21_*.c test_matrix.c -o test ${TEST_FLAGS}
	./test

# leaks:
#	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --log-file=leaks.log ./test >/dev/null 2>&1

style:
	clang-format -n --style=google *.c *.h

stylish:
	clang-format -i --style=google *.c *.h

