#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	int cols = 1, rows = 10, i, j;

	
	char** note = (char**) malloc(sizeof(char*)*rows);
	for (i = 0; i < rows; ++i) {
		*(note+i) = (char*) malloc(sizeof(char)*cols );
	}



	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j){
			note[i][j] = '3';
		}
	}

	for (i = 0; i < rows; ++i) {
		printf("%s\n", note[i]);
	}

	return 0;
}