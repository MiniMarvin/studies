/****************************************************************************************
 * @Author: Caio M. Gomes																*
 * @Date: 19/04/2017																	*
 * 																						*
 * @Problem: Find number that behaves on the following way: if x is not prime, 			*
 * there's a p, prime, that x-p also is a prime.										*
 * 																						*
 * @Algorithm: We receive the number, them we check if it's prime, if it isn't 			*
 * prime, them, if true, we check if it's even, them, by the Goldbach Strong			*
 * Conjecture it's necessary true.														*
 * If the number is odd, them we check if x is prime, if it isn't, them we check		*
 * if x-2 is a prime, if it's true them the analysis is true, if it isn't, them			*
 * the proposition is false.															*
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int isPrime(long int n);

int main(int argc, char const *argv[]) {
	
	long int n;
	int a;


	printf("Digit a number to check if it's a Valgueiro number: ");
	scanf(" %ld",&n);

	//printf("o numero %ld: %d\n", n, isPrime(n));

	//remove the numbers under 5 because, they aren't in the
	//Goldbatch theorem
	if(n <= 5) {
		printf("It isn't a Valgueiro Prime.\n");
		return 0;
	}

	a = isPrime(n);

	if(a == 1) {
		printf("It isn't a Valgueiro Prime.\n");
	} 

	else {
		/********************************************
		 * By the Goldbach Strong conjecture, any	*
		 * even number is a sum of two primes, so,	*
		 * for every x = 2k, x = p_1 + p_2, also,	*
		 * p_1 = x-p_2, them it's a Valgueiro number*
		 ********************************************/
		if(n%2 == 0) {
			printf("It's a Valgueiro Prime!!!\n");
		}

		else {
			/********************************************
			 * By the Goldbach Weak conjecture, any	odd *
			 * number is the sum of three other primes,	*
			 * since it's bigger than five. them, if 	*
			 * a number is odd and it's the sum of one	*
			 * even and from one odd numer, but the only*
			 * even prime is two, them, a Valgueiro odd	*
			 * number is a sum from a prime with 2.		*
			 ********************************************/
			a = isPrime(n-2);

			if(a == 1) {
				printf("It's a Valgueiro Prime!!!\n");
			}

			else {
				printf("It isn't a Valgueiro Prime.\n");
			}
		}

	}

	return EXIT_SUCCESS;
}


/**
 * @brief      Determines if prime.
 *
 * @param[in]  n     number to describe if is prime.
 *
 * @return     True if prime, False otherwise.
 */
int isPrime(long int n) {
	int flag = 0, divisor = 3;

	//check the canonical cases of mistake in the procedure
	if(n == 1) return 0;
	if(n == 2) return 1;
	if(n%2 == 0) return 0;

	else  {
		for (divisor = 3; divisor < n/2+1; divisor += 2) {
			if(n%divisor == 0) return 0;
		}
	}

	return 1;
}