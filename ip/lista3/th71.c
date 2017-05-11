//TODO: Rever todo o algoritmo.

#include <stdio.h>

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int main(int argc, char const *argv[]) {
	
	long int estoque[100] = {0};
	int ids[100];
	int n, m, i, j, k, ct;

	while(scanf(" %d", &n), n != 9999) {
		scanf(" %d", &m);
		ids[ct] = n;
		estoque[n] = m;
		// printf("id: %d, estoque: %d\n", ids[ct], estoque[ids[ct]]);
		ct++;
	}

	while(scanf(" %d", &i), i != 9999) {
		scanf(" %d %d", &j, &k);
		estoque[j] -= k;
		if(estoque[j] >= 0) {
			printf("OK\n");
			// printf("id: %d, estoque: %d\n", j, estoque[j]);
		}
		else {
			estoque[j] += k;
			printf("ESTOQUE INSUFICIENTE\n");
			// printf("id: %d, estoque: %d\n", j, estoque[j]);
		}
	}

	//bubble sort
	for (i = 0; i < ct-1; ++i) {
		for (j = i+1; j < ct; ++j) {
			if(ids[j] < ids[i]) {
				swap(&ids[i], &ids[j]);
			}
		}
	}

	for (i = 0; i < ct; ++i) {
		printf("%d %d\n", ids[i], estoque[ids[i]]);

	}

	return 0;
}