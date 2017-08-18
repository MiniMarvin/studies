#include <iostream>
#include <cstdio>

int abs(int x) {
	if(x < 0) return -x;
	return x;
}

int main(int argc, char const *argv[]) {
	
	int players[4] = {0}, diff[3];

	for (int i = 0; i < 4; ++i) {
		scanf(" %d", players + i);
	}

	/**
	 * 0 - 1 | 2 - 3
	 * 0 - 2 | 1 - 3
	 * 0 - 3 | 1 - 2
	 */

	diff[0] = abs( (players[0] + players[1]) - (players[2] + players[3]) );
	diff[1] = abs( (players[0] + players[2]) - (players[1] + players[3]) );
	diff[2] = abs( (players[0] + players[3]) - (players[1] + players[2]) );

	int small = diff[0];
	for (int i = 1; i < 3; ++i) {
		if(diff[i] < small) small = diff[i];
	}

	printf("%d\n", small);

	return 0;
}