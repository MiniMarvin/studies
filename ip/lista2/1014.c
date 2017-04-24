#include <stdio.h>
#include <stdlib.h>

int isPrime(int n, int *st);
void dividers(int n);

int main(int argc, char const *argv[]) {
	int n = 0, i = 0, a;

	scanf(" %d", &n);

	for (i = 0; i < n; ++i) {
		scanf(" %d", &a);
		dividers(a);
	}

	return EXIT_SUCCESS;
}

int isPrime(int n, int *st) {
	int i;

	if(*st < 3) *st = 3

	if(x == 2) return 1;
	if(x == 3) return 1;

	if(x%2 == 0) return 0;

	for (; *st < n/2 + 1; *st++) {
		if(i%n == 0) return 0;
	}

	return 1;
}

void dividers(int n) {
	int a = 3, b = 3, c = 0, i;

	if( isPrime(n, &a) ){
		puts("Primo");
	}

	b = a+1;

	while(b < n/2 && c == 0) {
		isPrime(n, &b);
		c = b%a;
	}

	if(c != 0) {
		puts("Quase Primo");
	}
	else {
		puts("Nem primo nem quase primo");
	}

}