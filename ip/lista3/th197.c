#include <stdio.h>
#include <stdib.h>

int main(int argc, char const *argv[]) {
	
	int num, arr**;

	scanf("%d", &num);

	arr = (int**) malloc(sizeof(int*)*num);
	for (i = 0; i < num; ++i) {
		*(arr+i) = (int*) malloc(sizeof(int)*num);
	}

	for (j = 0; j <= num/2; j++)
	{
		//iter down
		for (i = j; i < num - j; ++i) {
			scanf("%d", &arr[i][j]);
		}

		//iter right
		for (i = j+1; i < num - j; ++i) {
			scanf("%d", &arr[j][i]);
		}

		//iter up
		for (i = num - j; i >= j + 1; --i) {
			scanf("%d", &arr[i][j]);
		}

		//iter left
		for (i = num - j - 1; i >= j + 1; --i) {
			scanf("%d", &arr[j][i]);
		}
	}
	

	return 0;
}
