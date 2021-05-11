CFLAGS=-Wall -Wextra -Werror -Wpedantic -lm
CC=clang

test	:	test.o
	$(CC) $(CFLAGS) -o  test test.o
test.o	:
	$(CC) -c test.c
clean	:
	rm -f test test.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
