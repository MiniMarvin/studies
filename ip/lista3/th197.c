#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	
	int num, **arr, i, j;

	scanf("%d", &num);

	arr = (int**) malloc(sizeof(int*)*num);
	for (i = 0; i < num; ++i) {
		*(arr+i) = (int*) malloc(sizeof(int)*num);
	}

	for (j = 0; j <= num/2; j++) {

		// printf("%d\n", j);

		//iter down
		for (i = j; i < num - j; ++i) {
			scanf(" %d", &arr[i][j]);
			// printf("a: %d | %d\n", i, j);
		}

		//iter right
		for (i = j+1; i < num - j; ++i) {
			scanf(" %d", &arr[num - j - 1][i]);
			// printf("b: %d | %d\n", num - j - 1, i);
		}

		//iter up
		for (i = num - j - 2; i >= j; --i) {
			scanf(" %d", &arr[i][num - j - 1]);
			// printf("c: %d | %d\n", i, num - j - 1);
		}

		//iter left
		for (i = num - j - 2; i >= j + 1; --i) {
			scanf(" %d", &arr[j][i]);
			// printf("d: %d | %d\n", j, i);
		}
	}

	for (i = 0; i < num; ++i) {
		for (j = 0; j < num; ++j) {
			printf("%d\n", arr[i][j]);
		}
		// puts("");
	}
	

	return 0;
}
