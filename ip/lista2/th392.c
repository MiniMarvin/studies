#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

	int val, ct = 0, time = 0;
	float value = 10.0;

	while(scanf("%d", &val), val != 0) {
		if(ct < 10) {
			time += val;

			if(time > 40) {
				value += 0.2*(time-40);
				time = 40;
			}
		}
		else {
			value += 0.2*val;
		}
		ct++;
	}

	printf("%.2f\n", value);
	
	return 0;
}