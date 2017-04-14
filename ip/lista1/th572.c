#include <stdio.h>
#include <stdlib.h>

int main() {
	int x, y = 0;
	scanf(" %d", &x);
	if(x == 0) y += 2;

	scanf(" %d", &x);
	if(x) y += 1;

	scanf(" %d", &x);
	if(x) y += 1;

	scanf(" %d", &x);
	if(x) y += 1;

	scanf(" %d", &x);
	if(x) y += 3;

	if(y >= 5) printf("A Matrix esta em todo lugar. A nossa volta. E o mundo colocado diante de seus olhos, para que nao veja a verdade. Infelizmente e impossivel dizer o que e a Matrix. Voce tem de ver por si mesmo. *Voce e sugado pelo telefone e revelado a verdade\n");
	else printf("Voce precisa entender que a maioria dessas pessoas nao estao prontas para acordar. E muitos estao tao inertes, tao dependentes do sistema que vao lutar para protege-lo\n");


	return EXIT_SUCCESS;
}