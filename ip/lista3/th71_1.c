//TODO: Rever todo o algoritmo.
//obs: o id do produto pode ser negativo.

#include <stdio.h>
#define abs(x) (x > 0) ? x: -x

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int main(int argc, char const *argv[]) {
	
	int estoque[100] = {0}, estoque_negativo[100] = {0};
	int ids[100];
	int n, m, i, j, k, ct;

	while(scanf(" %d", &n), n != 9999) {
		scanf(" %d", &m);
		ids[ct] = n;
		if(n > 0)
			estoque[n] = m;
		else
			estoque_negativo[abs(n)] = m;
		// printf("id: %d, estoque: %d\n", ids[ct], estoque[ids[ct]]);
		ct++;
	}

	while(scanf(" %d", &i), i != 9999) {
		scanf(" %d %d", &j, &k);
		if(j > 0){
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
		else {
			j = abs(j);
			estoque_negativo[j] -= k;
			if(estoque_negativo[j] >= 0) {
				printf("OK\n");
				// printf("id: %d, estoque_negativo: %d\n", j, estoque_negativo[j]);
			}
			else {
				estoque[j] += k;
				printf("ESTOQUE INSUFICIENTE\n");
				// printf("id: %d, estoque: %d\n", j, estoque[j]);
			}
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