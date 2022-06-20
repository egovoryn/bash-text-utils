CC = gcc
LCHECK=-lcheck

all: clean s21_cat

test: s21_cat
	@$(CC) -o test_cat test_cat.c $(LCHECK)
	./test_cat

s21_cat: s21_cat.c
	$(CC) -c s21_cat.c -o s21_cat.o
	$(CC) s21_cat.o -o s21_cat

clean:
	rm -rf *.o *.a *.out *.hex *. 1 2 result
	rm -rf *.o s21_cat test_cat
