#include <bits/stdc++.h>

using namespace std;

bool f(int a, int b) {
	return (a > b);
}

void print_arr(int *arr, int b, int e) {
	for (int i = b; i < e; ++i) {
		cout << arr[i] <<  " ";
	}
	cout << endl;
}

int main() {
	
	int n, buff;
	int arr[1000];
	int orded[1000] = {0};

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	sort(arr, arr + n, f);

	for (int i = 0; i < n/2; i++) {
		orded[1 + 2*i] = arr[i];
	}
	for (int i = 0; i <= n/2; i++) {
		orded[2*i] = arr[n - i - 1];
	}

	// print_arr(arr, 0, n);
	print_arr(orded, 0, n);

	return 0;
}