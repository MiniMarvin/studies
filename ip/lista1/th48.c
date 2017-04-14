#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int num = 0;

	scanf("%d", &num);

	if(num%10 != 0) {
		if(num%(num/10) == 0) {
			printf("SIM\n");
			return EXIT_SUCCESS;
		}
	}

	printf("NAO\n");

	return EXIT_SUCCESS;
}