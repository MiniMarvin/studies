#include <bits/stdc++.h>

#define MAX_ELS 10
#define MAX_VAL 100

using namespace std;

typedef struct lst {
	lst *nxt;
	int key;
}lst;

lst* add_lst(lst* lista, int key);

int main() {

	srand(time(NULL));
	lst* lista = NULL;

	for (int i = 0; i < MAX_ELS; ++i) {
		lista = add_lst(lista, rand()%MAX_VAL);
	}

	while(lista != NULL) {
		printf("%d\n", lista->key);
		lista = lista->nxt;
	}

	return 0;
}

lst* add_lst(lst* lista, int key) {
	lst* el = lista;
	if(el == NULL){
		el = new lst();
		el->key = key;
		return el;
	}
	else{
		while(el->nxt != NULL) {
			el = el->nxt;
		}
		// found the element
		el->nxt = new lst();
		el->nxt->key = key;
		return lista;
	}
}