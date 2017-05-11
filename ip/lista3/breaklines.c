#include <stdio.h>

int main(int argc, char const *argv[]) {
	int num = 0, ct = 0;
	while(scanf(" %d", &num) != EOF) {
		ct++;
		printf("%d ", num);
		if(ct == 3) {
			printf("\n");
			ct = 0;
		}
	}
	return 0;
}