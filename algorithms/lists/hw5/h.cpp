#include <bits/stdc++.h>

#define lli long long int
#define MAX_SIZE 100000

using namespace std;

int main(int argc, char const *argv[]) {

	lli a, b, a1, b1;
	int cycles[MAX_SIZE];
	memset(cycles, -1, MAX_SIZE*sizeof(int));
	cycles[0] = cycles[1] = 1;

	while(scanf(" %d %d", &a, &b) != EOF) {
		
		int mx = 0;
		a1 = min(a, b);
		b1 = max(a, b);

		for (int i = a1; i <= b1; ++i) {
			int aux = i, ct = 0;
			// find the cycle
			while(1) {
				
				if(aux < MAX_SIZE) {
					if(cycles[aux] != -1 || aux == 1) {
						cycles[i] = ct + cycles[aux];
						break;
					}
				}

				ct++;

				if(aux%2) { // impar
					aux = 3*aux + 1;
				}
				else {
					aux /= 2;
				}
			}
			mx = max(cycles[i], mx);
			// cout << "(" << i << "," << cycles[i] << ")" << endl;
		}

		printf("%d %d %d\n", a, b, mx);
	}

	return 0;
}