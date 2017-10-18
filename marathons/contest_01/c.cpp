#include <bits/stdc++.h>

using namespace std;

long int absd(long int a, long int b) {
	return (b > a) ? b - a : a - b;
}

int main() {
	
	long int a, b, st;

	while(st = scanf(" %ld %ld", &a, &b), st != EOF) {
		cout << absd(b, a) << endl;
	}
	

	return 0;
}