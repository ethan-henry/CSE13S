#include <stdio.h>
CFLAGS=-Wall -Werror -Wpedantic -Wextra -Wshadow -std=c99
CC=clang $(CFLAGS)

sequence	:	sequence.o bv.o sieve.o
	$(CC) -o sequence sequence.o bv.o sieve.o -lm -g
sequence.o	:	sequence.c
	$(CC) -c sequence.c
bv.o	:	bv.c
	$(CC) -c bv.c
sieve.o	:	sieve.c
	$(CC) -c sieve.c
clean	:
	rm -f sequence sequence.o bv.o sieve.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
all	:	sequence
	$(CC) -c sequence.c bv.c sieve.c
