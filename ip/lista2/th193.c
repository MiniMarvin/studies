#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	
	unsigned long int area = 0, stars, i, ct = 0, buff;
	scanf(" %lu", &area);
	scanf(" %lu", &stars);

	for (i = 0; i < stars; ++i) {
		scanf(" %lu", &buff);
		if(buff*area >= 40000000) ct++;
		//printf("%d\n", i);
	}

	printf("%d\n", ct);

	return 0;
}