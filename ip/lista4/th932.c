#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void formatInput(char *str);
int strSize(char *str);

int main(int argc, char const *argv[]) {
	
	char str[200];
	while( scanf(" %200[^\n]", str), strcmp(str, "*") != 0 ) {
		// scanf("%[^\n]", str);
		formatInput(str);
		printf("%s\n", str);

	}
	
	return 0;
}


void formatInput(char *str) {
	int sz, i, ct = 0, begin = 0, state = 0, diff, j, end = 0;

	sz = strSize(str);

	for (i = 0; i < sz; ++i) {
		// Estado 0, em uma cadeia de espaços.
		if(state == 0) {
			if(str[i] != ' ') {
				
				state = 1;

				end = i;
				diff = end - begin;
				if(diff > 0) diff--; //Corrige o diff para usar depois.

				// Captaliza a letra inicial.
				if(str[i] <= 'z' && str[i] >= 'a'){
					str[i] += 'A' - 'a';
				}

				// Desloca a string.
				for (j = begin+1; j <= sz-diff; ++j) {
					str[j] = str[j+diff];
					// printf("val: %c\n", str[j+diff-1]);
				}

				sz -= diff; // Corrige a variável de tamanho da string.
				i -= diff;
			}
		}
		// Estado 2, procurando encontrar uma cadeia de espaços. 
		else if(state == 1) {
			begin = i;
			ct++;

			if(str[i] <= 'Z' && str[i] >= 'A') {
				str[i] -= 'A' - 'a';
			}

			if(str[i] == ' ') {
				// Corrige caso a palavra seja só de 1 caractere.
				if(ct <= 2) {
					str[i-ct] -= 'A' - 'a';
				}

				state = 0;
				i--;

				ct = 0;

			}
		}
	}

	str[sz] = '\0';

}

int strSize(char *str) {
	int i;
	for (i = 0; str[i] != '\0'; ++i);
	return i;
}