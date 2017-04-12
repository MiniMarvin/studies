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
	unsigned long int a, b, i = 0, anterior1 = 0, anterior2 = 1, atual = 0, flag = 0;;

	while(scanf(" %lu", &a), a != 0){
		
		flag = 1;

		for (i = 0; i < a - 1; ++i) {
			if(i == 0) atual = 0;
			
			else {
				atual = anterior1+anterior2;
			}

			anterior1 = anterior2;
			anterior2 = atual;

			printf("%lu ", atual);
		}
		printf("%lu", anterior1+anterior2);
		printf("\n");
	}

	if(fal)

	return 0;
}