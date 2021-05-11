CFLAGS=-Wall -Wextra -Werror -Wpedantic
CC=clang 

lrc	:	lrc.o
	$(CC) $(CFLAGS) -o lrc lrc.o
lrc.o	:
	$(CC) -c lrc.c
clean	:
	rm -f lrc lrc.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
