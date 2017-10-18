#include <bits/stdc++.h>

using  namespace std;

int maior(int *arr, int b, int e) {
	
	if(e - b < 1) {
		return e;
	}

	int k, u, v;
	k = (b + e)/2;
	u = maior(arr, b, k);
	v = maior(arr, k + 1, e);

	if(arr[u] > arr[v]) return u;
	return v;
}

int main() {

	int a, b;
	int *arr;

	scanf(" %d", &a);
	arr = new int[a];

	for (int i = 0; i < a; ++i) {
		scanf(" %d", &arr[i]);
	}
	int m = maior(arr, 0, a - 1);
	cout << m << " | " << arr[m] << endl;

	return 0;
}