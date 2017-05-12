#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]){
	int n, F, A, num;

	cin >> n;
	cin >> F;
	cin >> A;

	if(F < A) {
		num = n - A + F;
	}
	else {
		num = F - A;
	}

	cout << num << endl;
 
	return 0;
}