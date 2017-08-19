#include <stdio.h>
#include <stdlib.h>

typedef struct pessenger{
	int id;
	int date[3];
	char from[50];
	char to[50];
	int time[2];
	int chair;
	int age;
	char name[50];
} pessenger;

int main(int argc, char const *argv[]) {
	int val = 0, i = 0, j = 0, sum = 0;

	pessenger list[44];

	while(scanf(" %d", &list[i].id), (list[i].id != -1) && i < 44) {

		scanf(" %d/%d/%d", &(list[i].date[0]), &(list[i].date[1]), &(list[i].date[2]) );
		scanf(" %50[^\n]", &list[i].from);
		scanf(" %50[^\n]", &list[i].to);
		scanf(" %d:%d", &list[i].time[0], &list[i].time[1]);
		scanf(" %d", &list[i].chair);
		scanf(" %d", &list[i].age);
		scanf(" %50[^\n]", &list[i].name);

		i++;
	}

	for (j = 0, sum = 0; j < i; ++j) {
		sum += list[j].age;
	}

	sum = sum/i;

	for (j = 0; j < i; ++j) {
		if(list[j].age > sum && (list[j].chair%2 == 0) ) printf("%s\n", list[j].name);
	}

	return 0;
}