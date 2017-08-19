#include <stdio.h>
#include <stdlib.h>

typedef struct BusStop{
	int wait;
	int travel;
} busStop;

int main(int argc, char const *argv[]) {
	int val = 0, i = 0, sum = 0, a = 0;

	scanf(" %d", &val);

	busStop path[val];

	

	//get all the wait times.
	for (i = 0; i < val; ++i) {
		scanf(" %d", &(path[i].travel) );
	}

	//get all the travel times.
	for (i = 0; i < val; ++i) {
		scanf(" %d", &(path[i].wait) );
	}

	//calculate the spent time.
	sum = path[0].travel;

	for (i = 1; i < val; ++i) {
		a = sum%path[i].wait;

		if( a != 0 )sum += path[i].wait - a;

		sum += path[i].travel;
	}

	printf("%d\n", sum);

	return 0;
}