#include <stdio.h>
#include <stdlib.h>

#define __LIST_SIZE 100

typedef struct mercadoria {
	int id;
	int quantidade;
} mercadoria;

int main(int argc, char const *argv[]) {
	
	int ct = 0, i, client, here;
	mercadoria list[__LIST_SIZE], buff;

	//garante zero para todas as quantidades.
	for (i = 0; i < __LIST_SIZE; ++i) {
		list[i].quantidade = 0;
	}

	while( scanf(" %d", &buff.id), buff.id != 9999 ) {
		scanf(" %d", &buff.quantidade);

		here = 0;

		//verifica se o produto já está cadastrado.
		for (i = 0; i < ct; ++i) {
			if(buff.id == list[i].id) {
				here = 1;
				break;
			}
		}

		// se encontrou o número o i é o index do array onde ele está armazenado, se não i é um número acima do que estava registrado.
		list[i].id = buff.id; 
		list[i].quantidade += buff.quantidade; 

		if(here == 0) ct++;

	}

	while( scanf(" %d", &client), client != 9999 ) {
		scanf(" %d %d", &buff.id, &buff.quantidade);

		here = 0;

		//verifica se o produto já está cadastrado.
		for (i = 0; i < ct; ++i) {
			if(buff.id == list[i].id) {
				here = 1;
				break;
			}
		}

		if(here == 1){
			list[i].quantidade -= buff.quantidade;
			if(list[i].quantidade >= 0) {
				printf("OK\n");
			}
			else {
				printf("ESTOQUE INSUFICIENTE\n");
				list[i].quantidade += buff.quantidade;
			}
		}
		else printf("ESTOQUE INSUFICIENTE\n");

	}

	for (i = 0; i < ct; ++i) {
		printf("%d %d\n", list[i].id, list[i].quantidade);
	}

	return 0;
}