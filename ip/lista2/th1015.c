#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	double x, y, s_x2 = 0, s_x = 0, s_y = 0, s_xy = 0;
	double a, b, d;
	int i = 1, n = 0;

	scanf(" %d", &n);

	for (i = 0; i < n; ++i) {
		scanf(" %lf %lf", &x, &y);
		s_x2 += x*x;
		s_x += x;
		s_y += y;
		s_xy += x*y;
	}

	d = n*s_x2 - s_x*s_x;
	a = (n*s_xy - s_x*s_y)/d;
	b = (s_x2*s_y - s_x*s_xy)/d;

	printf("A: %.2f\nB: %.2f\n", a, b);
	
	return 0;
}