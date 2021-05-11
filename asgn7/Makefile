CFLAGS=-Wall -Werror -Wpedantic -Wextra -Wshadow -std=c99 -g
CC=clang $(CFLAGS)

all	:	encode decode decode_test
encode	:	encode.o io.o trie.o word.o
	$(CC) -o encode encode.c trie.c word.c io.c -lm
decode	:	decode.o io.o trie.o word.o
	$(CC) -o decode decode.c trie.c word.c io.c -lm
decode_test	:	decode_test.o io.o trie.o word.o
	$(CC) -o decode_test decode_test.c trie.c word.c io.c -lm
encode.o	:	encode.c
	$(CC) -c encode.c
decode.o	:	decode.c
	$(CC) -c decode.c
decode_test.o	:	decode_test.c
	$(CC) -c decode_test.c
test.o	:	test.c
	$(CC) -c test.c
io.o	:	io.c
	$(CC) -c io.c
trie.o	:	trie.c
	$(CC) -c trie.c
word.o	:	word.c
	$(CC) -c word.c
clean	:
	rm -f encode decode encode.o decode.o io.o trie.o word.o
infer:
	make clean; infer-capture -- make; infer-analyze -- make
