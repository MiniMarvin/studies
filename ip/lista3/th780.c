#include <stdio.h>
#include <stdlib.h>

void printLine(int line[], int size);

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int main(int argc, char const *argv[]) {
	char action;
	int list[10000], ask, ct = 0;
	int found = 0, i;
	int mct = 0;

	while( scanf(" %c", &action) != EOF ) {
		switch(action) {
			case 'a':
				scanf(" %d", &ask);
				found = 0;
				for (i = 0; i < ct; ++i) {
					if(list[i] == ask) {
						found = 1;
						break;
					}
				}
				if(found == 0) {
					list[i] = ask;
					ct++;
				}
				break;
			case 'r':
				scanf(" %d", &ask);
				found = 0;
				for (i = 0; i < ct; ++i) {
					if(list[i] == ask) {
						found = 1;
						break;
					}
				}
				if(found == 1) {
					ct--;
	    			//vai trocando a posição deles até chegar ao ultimo.
	    			for (i; i < ct; ++i) {
	    				swap(&list[i], &list[i+1]);
	    			}
					printf("removido\n");
				}
				else printf("falha\n");
				break;
			case 'p':
				printLine(list, ct);
		}
	}

	return 0;
}

void printLine(int line[], int size) {
	int i;
	if(size == 0) {
		printf("vazia\n");
		return;
	}

	for (i = 0; i < size-1; ++i) {
		printf("%d ", line[i]);
	}
	printf("%d\n", line[i]);
}