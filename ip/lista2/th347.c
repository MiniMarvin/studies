#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	int n, sum = 0, val = 0, i, b1, b2;
	char code;

	scanf(" %d", &n);

	for (i = 1; i <= n; ++i) {
		sum += val+i;
		val += i;
	}

	b1 = val%2;
	b2 = sum%2;
	if(b1 == 0 && b2 == 0) {
		code = 'P';
	} else if(b1 ==1 && b2 == 1){
		code = 'I';
	} else {
		code = 'N';
	}

	printf("%d %d %c\n", val, sum, code);

	return 0;
}