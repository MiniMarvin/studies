#include <stdio.h>
#include <stdlib.h>

#define abs (a > 0)? a:-a

int main() {
	unsigned int a, buff[20], i = 0, b = 0;

	scanf(" %d", &a);

	do{
		buff[i++] = a%10;
	}
	while( (a /= 10) > 0);

	a = --i;
	b = i/2;

	for (i; i > b; i--) {

		if(buff[i] != buff[a-i]){
			printf("N\n");
			return EXIT_SUCCESS;
		}

	}
	
	printf("S\n");

	return EXIT_SUCCESS;
}