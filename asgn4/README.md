ERROR(S):
	When using make infer, the program is said to have a Memory Leak.  This is a false alarm, however, as a pass through with
	valgrind shows that there is no way for a Memory Leak to take place.

OVERVIEW:
	Program finds all Prime numbers between a specified number and 0.  Also finds palendromin primes in different bases
	and prints Lucas Primes, Mercenne Primes, and Fibonacci Primes

COMPILING/RUNNING:
	./sequence
	OPTIONS:
		-n <number>: Max number, inclusive, to search.  Defaults at 1000
		-s: Prints Palendromic Primes
		-p: Prints Special Primes
