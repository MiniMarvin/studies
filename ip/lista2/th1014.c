#include <stdio.h>
#include <stdlib.h>

int isPrime(long int n);
void primeDivisors(long int n, int *ct, int *ct1);
void trata(long int n);

int main(int argc, char const *argv[]) {
	
	unsigned long int i, n, buff;

	scanf(" %lu", &n);

	for (i = 0; i < n; ++i) {
		scanf(" %d", &buff);
		// printf("%d | ", buff);
		trata(buff);
	}

	return 0;
}


int isPrime(long int n) {
	int i;

	if(n == 2) return 1;
	if(n == 3) return 1;
	
	if(n%2 == 0) return 0;

	for (i = 3; i < n/2 + 1; i+=2) {
		if(n%i == 0) {
			return 0;
		}
	}

	return 1;
}

void primeDivisors(long int n, int *ct, int *ct1) {
	// long int primes[100], ct = 0, i, j;
	long int i, j;
	*ct = 0;
	*ct1 = 0;

	if(n%2 == 0) {
		(*ct)++;
		j = n/2;
		while(j%2 == 0 && j != 0) {
			j /= 2;
			(*ct1)++;
		}
	}

	for (i = 3; i < n/2 + 1; i += 2) {
		if (n%i == 0) {
			//TODO: check if prime based on the already gotten primes.
			if (isPrime(i)) {
				(*ct)++;
				j = n/i;
				while(j%i == 0 && j != 0) {
					j /= i;
					(*ct1)++;
				}
			}
		}
	}
}

void trata(long int n) {
	int ct = 0, ct1 = 0;
	// printf("n: %d | p: %d\n", n, isPrime(n));
	if(isPrime(n) == 1) {
		printf("Primo\n");
		return;
	}

	primeDivisors(n, &ct, &ct1);
	// printf("n: %d | ct: %d | ct1: %d\n", n, ct, ct1);
	if (ct == 2 && ct1 == 0) {
	// if (ct == 2) {
		puts("Quase primo");
		return;
	}

	puts("Nem primo nem quase primo");
}