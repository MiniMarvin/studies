#include <bits/stdc++.h>

using namespace std;

void printarr(int *arr, int size) {
	for (int i = 0; i < size; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

bool decreasing (int i, int j) { 
	return (i > j);
}

// sort the array and them just print it in those cases
int main() {

	int *arr = new int[100000];
	int cases, t, buff, ct;

	cin >> cases;

	for (int i = 0; i < cases; ++i) {
		
		cin >> t;
		ct = 0;

		for (int j = 0; j < t; ++j) {
			cin >> buff;

			if(buff == 1) {
				ct++;
			}

			arr[j] = buff;
		}

		sort(arr, arr+t, decreasing);

		if(arr[0] == 3 && arr[1] == 2 && t - ct == 2) {
			
			for (int j = 0; j < ct; ++j) {
				cout << 1 << " ";
			}

			sort(arr, arr + (t - ct));
			printarr(arr, (t - ct));
		}
		else {
			
			for (int j = 0; j < ct; ++j) {
				cout << 1 << " ";
			}
			
			printarr(arr, t - ct);
		}
	}

	return 0;
}