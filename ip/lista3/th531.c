#include <stdio.h>

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int main(int argc, char const *argv[]) {
	int arr[200], ct = 0, i, j, k, num, menor = i;

	while(scanf("%d", &num) != EOF) {
		arr[ct] = num;
	    ct++;
	}

	// ct--;

	for (i = 0; i < ct - 1; ++i) {
		menor = i;
		for (k = i; k < ct; k++) {
			if(arr[k] < arr[menor]) {
				menor = k;
			}
		}

		swap(&arr[i], &arr[menor]);

		printf("Menor elemento neste passo: %d\n", arr[i]);
		printf("Estado Atual: ");
		for (j = 0; j < ct-1; ++j) 
			printf("%d | ", arr[j]);
		printf("%d\n\n", arr[ct-1]);
	}

	printf("Resultado Final: ");
	for (j = 0; j < ct-1; ++j) 
		printf("%d | ", arr[j]);
	printf("%d\n\n", arr[ct-1]);

	return 0;
}