#include <stdio.h>
#include <stdlib.h>

#define abs(x) (x < 0) ? -x : x

int main(int argc, char const *argv[]) {
	int x, y, z, i = 0, t = 0, a, b, c;
	scanf(" %d\n%d\n%d", &x, &y, &z);

	t = x;

	for (i = 0; i < z; ++i) {
		scanf(" %d %d %d", &a, &b, &c);
		t -= 4*y + a + b + c;
		if(t <= 0) {
			printf("%d %d\n", i+1, t);
			return 0;
		}
	}
	
	printf("%d\n", t);

	return 0;
}