#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	// int size, i, j, maior[3] = {0};
	int size, i, j, maior = 0;
	char arr[100][100]; //alloc the board that the pacman already passed.
	int value = 0;
	char buff;

	scanf(" %d", &size);

	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j) {
			scanf(" %c", &arr[i][j]);
		}
	}

	for (i = 0; i < size; i++) {
		
		for (j = 0; j < size; ++j) {
			if(arr[i][j] == 'o') value++;
			else if(arr[i][j] == 'A') value = 0;

			if(value > maior) maior = value;
		}

		i++;

		for (j = size - 1; j >= 0; --j) {
			if(arr[i][j] == 'o') value++;
			else if(arr[i][j] == 'A') value = 0;

			if(value > maior) maior = value;
		}

	}

	printf("%d\n", maior);

	return 0;
}