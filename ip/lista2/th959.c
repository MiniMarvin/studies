#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	int x, y, z, i = 1, j = 0;
	scanf(" %d %d %d", &x, &y, &z);

	while(i <= y) {

    	printf("%d", i);
		i += z;

		if(++j >= x) {
			j = 0;
			printf("\n");
		}
		else printf(" ");
	}
	printf("\n");
	
	return 0;
}