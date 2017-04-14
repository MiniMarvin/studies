#include <stdio.h>
#include <stdlib.h>

int main() {
	float x, y, z, media = 0;
	int mt = 0;

	scanf(" %f", &x);
	scanf(" %f", &y);
	scanf(" %f", &z);

	media = (x+y+z)/3.0;

	if(x > media) mt++;
	if(y > media) mt++;
	if(z > media) mt++;
	
	printf("%d\n", mt);

	return EXIT_SUCCESS;
}