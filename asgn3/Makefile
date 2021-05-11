CFLAGS=-Wall -Werror -Wpedantic -Wextra -Wshadow
CC=clang $(CFLAGS)

pathfinder	:	pathfinder.o stack.o
	$(CC) -o pathfinder pathfinder.o stack.o
pathfinder.o	:	pathfinder.c
	$(CC) -c -g pathfinder.c
stack.o	:	stack.c
	$(CC) -c -g stack.c
clean	:
	rm -f pathfinder pathfinder.o stack.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
all	:	pathfinder
	$(CC) -c pathfinder.c stack.c
