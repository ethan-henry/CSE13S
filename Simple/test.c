#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(long num) {
	if (num <= 1 || num % 2 == 0 || num % 3 == 0) {
		return false;
	}

	int i = 5;
	while(pow((double)i, 2) <= num) {
		if (num % i == 0 || num % (i + 2) == 0) {
			return false;
		}
		i += 6;
	}
	return true;
}

int main() {
	long largest = 0;
	for (long x = 600851475142; x > 0; x--) {
		if (x % 600851475143 == 0) {
			if (is_prime(x)) {
				largest = x;
				printf("%ld\n", largest);
			}
		}
	}
	printf("%ld\n", largest);
}
