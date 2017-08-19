/**
 * Print all odd numbers in a range.
 **/

#include <stdio.h>

void swap(int *a, int *b){
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

int main(int argc, char const *argv[]) {
	unsigned int a, b, i = 0;

	scanf(" %u", &a);
	scanf(" %u", &b);

	for (i = a; i <= b; ++i) {
		if(i%2 == 1) printf("%u\n", i);
	}

	return 0;
}