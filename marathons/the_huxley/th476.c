#include <stdio.h>
#include <stdlib.h>

typedef struct user {
	char name[20];
	int sex;
	int id;
	int level;
	int atk;
	int def;
} user;

int main(int argc, char const *argv[]) {
	int num = 0, i;
	scanf(" %d", &num);

	user a[num];

	for (i = 0; i < num; ++i) {
		
		scanf(" %50[^\n]", &a[i].name);
		scanf(" %d", &a[i].sex);
		scanf(" %d", &a[i].id);
		scanf(" %d", &a[i].level);
		scanf(" %d", &a[i].atk);
		scanf(" %d", &a[i].def);

		
		printf("Nome: %s\n", a[i].name);
		printf("ID: %d\n", a[i].sex);
		printf("Level: %d\n", a[i].id);
		printf("Vida: %d\n", a[i].level);
		printf("Ataque: %d\n", a[i].atk);
		printf("Defesa: %d\n", a[i].def);
	}

	return 0;
}