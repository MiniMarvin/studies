#include <bits/stdc++.h>

using namespace std;

long int absd(long int a, long int b){
	long int df = a - b;
	return (df > 0) ? df : -df;
}

int main() {

	long int x0, y0, pt, mx = 0, my = 0, minx, miny, diff, buff;

	cin >> pt;
	cin >> x0;
	cin >> y0;

	mx = x0;
	my = y0;
	minx = x0;
	miny = y0;

	for (int i = 1; i < pt; ++i) {
		cin >> x0;
		cin >> y0;
		// diff = absd(x1, x0);
		if(x0 > mx) {
			mx = x0;
		}
		
		if(y0 > my) {
			my = y0;
		}

		if(x0 < minx) {
			minx = x0;
		}
		
		if(y0 < miny) {
			miny = y0;
		}
	}

	diff = absd(minx, mx);
	buff = absd(miny, my);

	if(diff > buff){
		buff = diff*diff;
		cout << buff << endl;
	}
	else {
		buff = buff*buff;
		cout << buff << endl;
	}

	return 0;
}