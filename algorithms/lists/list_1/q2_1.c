#include <stdio.h>
#include <stdlib.h>

int main() {

	//int *numeros = malloc(sizeof(int)*1000000);
	int *numeros = malloc(4000000);
	int in_num, action;
	int register ct = -1, i;

	scanf(" %d", &in_num);

	for (i = 0; i < in_num; ++i) {
		scanf(" %d", &action);
		if(action == 1) {
			ct++;
			scanf(" %d", &numeros[ct]);
		}
		else if(action == 2) {
			// remove();
			//numeros++;
			if(ct >= 0) ct--;
		}
		else {
			//printf("%d\n", numeros[0]);
			if(ct < 0) {
				printf("Empty!\n");
			}
			else {
				printf("%d\n", numeros[ct]);
			}
		}
	}


	return 0;
}
