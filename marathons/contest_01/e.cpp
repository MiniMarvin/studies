#include <bits/stdc++.h>

using namespace std;

int main() {
	
	int pairs[1000000], ct = 0, buff, num, max = 0;

	cin >> num;
	
	// garantee that everyone is 0
	for (int i = 0; i < num; ++i) {
		pairs[i] = 0;
	}

	for (int i = 0; i < 2*num; ++i) {
		cin >> buff;
		pairs[buff]++;

		if(pairs[buff] == 1) {
			ct++;
			if(ct > max) max = ct;
		}
		else if(pairs[buff] == 2) {
			ct--;
		}
	}

	cout << max << endl;

	return 0;
}