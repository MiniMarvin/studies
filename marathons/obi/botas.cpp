#include <bits/stdc++.h>
#include <cstdio>

// #define lower_from(a, b) (a < b) ? a : b

using namespace std;

typedef struct shoe {
	int size;
	char side;
} shoe;

void swap_shoe(shoe* a, shoe* b) {
	shoe t = *a;
	*a = *b;
	*b = t;
}

int lower_from(int a, int b) {
	if (a < b) return a;
	return b;
}

int main(int argc, char const *argv[]){
	int boots_num, boot_size, buff, begin, end, left, right, pairs = 0, i, j;
	char boot_side;

	cin >> boots_num;

	shoe sapatos[boots_num];

	for (i = 0; i < boots_num; i++) {
		cin >> sapatos[i].size;
		cin >> sapatos[i].side;
	}

	//sort by size
	for (i = 0; i < boots_num; ++i) {
		for (j = i; j < boots_num; ++j) {
			if(sapatos[i].size > sapatos[j].size ) 
				swap_shoe(&sapatos[i], &sapatos[j]);
		}
	}

	// plot everything sorted
	// for (i = 0; i < boots_num; ++i) {
	// 	cout << sapatos[i].size << " | " << sapatos[i].side << endl;
	// }

	//make the pairing
	for (i = 0; i < boots_num;) {
		
		begin = i;
		end = i;
		buff = sapatos[begin].size;
		left = 0;
		right = 0;

		for (j = i; ; ++j) {			
			end++;

			if(sapatos[j].side == 'D') {
				right++;
				// cout << "found r: " << i << " | " << j << endl;
			}
			if(sapatos[j].side == 'E') {
				left++;
				// cout << "found l: " << i << " | " << j << endl;
			}

			if(sapatos[j+1].size != sapatos[j].size) break; //break the ordering for different sizes.
			
		}

		buff = lower_from(left, right);
		pairs += buff;

		i = end;

	}

	cout << pairs << endl;

	return 0;
}
