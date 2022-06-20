CC = gcc
LCHECK=-lcheck

all: clean s21_grep

test: s21_grep
	@$(CC) -o test_grep test_grep.c $(LCHECK)
	./test_grep

s21_grep: s21_grep.c
	$(CC) -c s21_grep.c -o s21_grep.o
	$(CC) s21_grep.o -o s21_grep

clean:
	rm -rf  *.o *.a *.out 1 2
	rm -rf *.o s21_grep test_grep
