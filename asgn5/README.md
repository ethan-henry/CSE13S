Purpose: Testing the speed of different sorting functions

Compiling:
	make: makes the program
	make clean: cleans all compiler created files
	make all: same as make
	make infer: runs infer for errors

Options:
	-p: Number of numbers to print.  DEFAULT: 100
	-n: Number of numbers to sort. DEFAULT: 100
	-r: Random seed. DEFAULT: 8222022
	-A: Run all sorting algorithms
	-b: Run Bubble Sort
	-s: Run Shell Sort
	-q: Run Quick Sort
	-i: Run Binary Insertion Sort

IMPORTANT:
	command arguments are non-exclusive. Any can be run at 1 time, or all.

ERRORS:
	There are no errors when code is run with valgrind or infer
