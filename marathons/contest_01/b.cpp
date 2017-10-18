#include <bits/stdc++.h>

using namespace std;

int main() {
	
	char str[1000];
	int num, let[26] = {0}, mv = 0, diff = 0, sz = 0, min = 0;

	scanf("%s1000^[\n]", &str);
	// cout << str << endl;
	cin >> num;

	sz = strlen(str);

	if(sz < num) {
		cout << "impossible" << endl;
		return 0;
	}

	for (int i = 0; i < sz; ++i) {
		let[str[i] - 'a']++;
		// cout << (str[i]) << ": " << let[str[i] - 'a'] << endl;
	}

	for (int i = 0; i < 26; ++i) {
		if(let[i] > 0) {
			diff++;
			mv += let[i] - 1;
		}
	}

	while(num > diff) {
		min++;
		diff++;
	}
	cout << min << endl;

	return 0;
}