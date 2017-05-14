#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

	int size_1, size_2, i, j, k = 0;
	int *pol_1, *pol_2, *pol;
	
	
	while(scanf(" %d %d", &size_1, &size_2) != EOF) {

		// printf("%d %d\n", size_1, size_2);

		pol_1 = (int*) malloc(sizeof(int)*(size_1+1));
		pol_2 = (int*) malloc(sizeof(int)*(size_2+1));
		pol = (int*) malloc(sizeof(int)*(size_2 + size_1 + 1));

		for (i = 0; i <= size_1; ++i) {
			scanf(" %d", &pol_1[i]);
			// printf("%d\n", pol_1[i]);
			pol[i] = 0;
		}

		for (i = 0; i <= size_2; ++i) {
			scanf(" %d", &pol_2[i]);
			// printf("%d\n", pol_2[i]);
			pol[size_1 + i] = 0;
		}

		for (i = 0; i <= size_1; ++i) {
			for (j = 0; j <= size_2; ++j) {
				pol[i+j] += pol_1[i]*pol_2[j];
			}
		}

		printf("Caso #%d: ", ++k);
		for (i = 0; i < size_1 + size_2; ++i) {
			printf("%d ", pol[i]);
		}
		printf("%d", pol[i]);

		puts("");

		free(pol_1);
		free(pol_2);
	}
	
	return 0;
}