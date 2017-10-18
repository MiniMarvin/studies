#include <bits/stdc++.h>

using namespace std;

int main() {

	int a, b, res;
	char op;


	// TODO: uma boa forma de coletar esses dados
	while(scanf(" %d%c%d", &a, &op, &b), op != '+' && op != '-') {

	}

	if(op == '-') {
		res = a - b;
	}
	else if(op == '+') {
		res = a + b;
	}

	// print
	if(res <= 0) {
		for (int i = 0; i < 48; ++i) {
			cout << "+";
		}
		cout << ".";
	}
	else if(res <= 9) {
		for (int i = 0; i < 48 + res; ++i) {
			cout << "+";
		}
		cout << ".";
	}
	else if(res >= 10 && res < 100) {
		for (int i = 0; i < 48 + res/10; ++i) {
			cout << "+";
		}
		cout << ".>";
		for (int i = 0; i < res%10; ++i) {
			cout << "+";
		}
		cout << ".";
	}

	else {
		for (int i = 0; i < 48 + res/100; ++i) {
			cout << "+";
		}
		cout << ".>";
		for (int i = 0; i < (res%100)/10; ++i) {
			cout << "+";
		}
		cout << ".>";
		for (int i = 0; i < res%10; ++i) {
			cout << "+";
		}
		cout << ".";
	}

	return 0;
}