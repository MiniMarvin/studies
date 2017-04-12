/**
 * Print all odd numbers in a range.
 **/

#include <stdio.h>

/*
void swap(int *a, int *b){
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
*/

//look up untill find a number multiple, them, keep adding until pass the biggest number
int main(int argc, char const *argv[]) {
	unsigned int a, b, c, i = 0, flag = 0;

	scanf(" %u", &a);
	scanf(" %u", &b);
	scanf(" %u", &c);

	for (i = b; i < c && flag == 0; ++i) {
		if(i%a == 0) flag = 1;
	}

	if(flag == 0) printf("INEXISTENTE\n");
	else {
		for (i--; i <= c; i += a) {
			printf("%d\n", i);
		}
	}


	return 0;
}