#include <stdio.h>
#include <stdlib.h>

typedef struct user {
	int age;
	char name[50];
	char sex;
	char civil_state;
	int friends;
	int photos;
} user;

int main(int argc, char const *argv[]) {
	int num = 0, i;
	scanf(" %d", &num);

	user a[num];

	for (i = 0; i < num; ++i) {
		scanf(" %d", &a[i].age);
		scanf(" %50[^\n]", &a[i].name);
		scanf(" %c", &a[i].sex);
		scanf(" %c", &a[i].civil_state);
		scanf(" %d", &a[i].friends);
		scanf(" %d", &a[i].photos);

		printf("Idade: %d\n", a[i].age);
		printf("Nome: %s\n", a[i].name);
		printf("Sexo: %c\n", a[i].sex);
		printf("Estado Civil: %c\n", a[i].civil_state);
		printf("Numero de amigos: %d\n", a[i].friends);
		printf("Numero de fotos: %d\n\n", a[i].photos);
	}

	return 0;
}