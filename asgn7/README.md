ERROR:
	INFER:
		NULL_DEREFERENCE: Not true, as there is a test to make sure this is not the case
		MEMORY_LEAK: Again, not true as there is a test to make sure it never happens
SYNOPSIS:
	This set of programs allows for a file to be input and compressed, and then decompressed using Lempel-Ziv 78 Compression

OPTIONS:
	-v: Compression statistics
	-i: The input file (DEFAULT: standard input)
	-o: The ouput file: (DEFAULT: standard output)

COMPILING:
	make: makes all the programs
	make all: makes all the programs
	make decode: makes the decode program
	make encode: makes the encode program
	make clean: removes all compiler created files
	make infer: runs infer
