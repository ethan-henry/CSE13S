#include <stdio.h>
CFLAGS=-Wall -Wextra -Werror -Wpedantic -Wshadow
CC=clang $(CFLAGS)

.PHONY : all clean

math	:	math.o
	$(CC) -o math math.o -lm
math.o	:	math.c
	$(CC) -c math.c 
clean	:
	rm -f math math.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
all	:	math
	$(CC) -c math.c

