#include <stdio.h>

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int main(int argc, char const *argv[]) {
	int arr[100], ct = 0, i, j, k, num;

	while(scanf("%d", &num) != EOF) {
		arr[ct] = num;
	    ct++;
	}

	// ct--;

	for (i = 1; i < ct; ++i) {
		
		printf("Chave: %d\n", arr[i]);
		printf("Estado Atual: ");
		for (j = 0; j < ct-1; ++j) 
			printf("%d | ", arr[j]);
		
		printf("%d\n", arr[ct-1]);

		for (k = i; k > 0; k--) {
			if(arr[k] < arr[k-1]) {
				swap(&arr[k], &arr[k-1]);
				for (j = 0; j < ct-1; ++j) 
					printf("%d | ", arr[j]);
				printf("%d\n", arr[ct-1]);
			}
		}
		printf("\n");
	}

	printf("Resultado Final: ");
		for (j = 0; j < ct-1; ++j) 
			printf("%d | ", arr[j]);
		
		printf("%d\n", arr[ct-1]);

	return 0;
}