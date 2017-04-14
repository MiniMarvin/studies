#include <stdio.h>
#include <stdlib.h>

int main() {
	int x, y;
	scanf(" %d\n%d", &x, &y);

	printf("%d\n%d\n%d\n%d\n%d\n%d\n", (x > y), (x == y), (x < y), (x != y), (x >= y), (x <= y));

	return EXIT_SUCCESS;
}