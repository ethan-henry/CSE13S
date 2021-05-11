CFLAGS=-Wall -Werror -Wpedantic -Wextra -Wshadow -std=c99
CC=clang $(CFLAGS)

sorting	:	sorting.o bubble.o quick.o shell.o binary.o
	$(CC) -o sorting sorting.o quick.o shell.o binary.o bubble.o -lm -g
sorting.o	:	sorting.c
	$(CC) -c sorting.c
bubble.o	:	bubble.c
	$(CC) -c bubble.c
quick.o	:	quick.c
	$(CC) -c quick.c
shell.o	:	shell.c
	$(CC) -c shell.c
binary.o	:	binary.c
	$(CC) -c binary.c
clean	:
	rm -f sorting binary quick shell bubble *.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
all	:	sorting
	$(CC) -c sorting.c bubble.c binary.c shell.c quick.c
