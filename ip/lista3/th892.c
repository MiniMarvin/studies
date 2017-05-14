#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	
	int i, j, k, l, rows, cols;
	char** arr;

	scanf(" %d %d", &rows, &cols);

	arr = (char**) malloc(sizeof(char*)*rows);

	for (i = 0; i < rows; ++i) {
		*(arr+i) = (char*) malloc(sizeof(char)*cols); //alloc the cols for every line.
		scanf(" %s", arr[i]);
		// printf("pt_1: %d\n", i);
	}

	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			// printf("pt_2: (%d, %d)\n", i, j);
			//found a tower
			if(arr[i][j] == '&') {
				//check if in it's around there's a enemy
				for (k = -1; k <= 1; k++) {
					for (l = -1; l <= 1; ++l) {
						if(i+k >= 0 && j+l >= 0){
							if(arr[i+k][j+l] == '*') arr[i+k][j+l] = '.'; 
						}
					}
					
				}
			}
		}
	}

	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if(arr[i][j] == '*'){
				printf("N\n");
				return 0;
			}
		}
	}

	printf("S\n");

	return 0;
}