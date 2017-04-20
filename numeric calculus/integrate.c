#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define f(x) 2*pow(x, 3)

int main(int argc, char const *argv[]) {
	
	long double dx = 0.000000001, x = 0, a, b, integral = 0;
	printf("Digite o inicio do intervalo: ");
	scanf(" %Lf", &a);
	printf("Digite o final do intervalo: ");
	scanf(" %Lf", &b);

	x = a;

	while(x <= b) {
		x += dx;
		integral += dx*f(x);
	}

	printf("int: %Lf\n", integral);

	return 0;
}