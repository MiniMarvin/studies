#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	int read, num;
	//The number is 
	
	while(scanf(" %d", &read), read != 0) {
		num = read/2;
		printf("%d - %d\n", (num + 1)*(num + 1), num*num );
	}

	return 0;
}