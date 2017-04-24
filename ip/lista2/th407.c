#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

int seqSize(int n);

int main(int argc, char const *argv[]) {
	int a = 0, b = 0, big = 0, buff = 0, u, flag = 0;

	while( scanf(" %d %d", &a, &b) != EOF ) {
		if(a > b) {
			flag = 1;
			swap(&a, &b);
		} 
		else {
			flag = 0;
		}

		u = a;
		big = 0;
		for (a; a <= b; a++) {
			buff = seqSize(a);
			if(buff > big) big = buff;
		}

		if(flag == 0) printf("%d %d %d\n", u, b, big);
		else printf("%d %d %d\n", b, u, big);
	}

	return 0;
}

int seqSize(int n) {
	int ct = 1;
	while(n != 1) {
		if (n%2 == 0) n /= 2;
		else n = 3*n + 1;
	    ct++;
	}
	return ct;
}