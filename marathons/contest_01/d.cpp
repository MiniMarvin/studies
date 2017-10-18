#include <bits/stdc++.h>

using namespace std;

int main() {
	
	long int a, b, st = 0, al[26] = {0};
	char str[1000];

	cin >> a; 
	cin >> b;

	if(b >= a) {
		cout << "YES" << endl;
		return 0;
	}

	scanf(" %s1000^[\n]", str);
	st = strlen(str);

	for (int i = 0; i < st; ++i) {
		al[str[i] - 'a']++;
	}

	for (int i = 0; i < 26; ++i) {
		
		if(al[i] > b) {
			cout << "NO" << endl;
			return 0;
		}
	}

	cout << "YES" << endl;

	return 0;
}