// Implementação de Árvore binária em C
#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
	int balance;
	int key;
	int pos;
	struct tree* left;
	struct tree* right;
} tree;

// Prototypes
tree* insert(tree* root, int key); 
int find_pos(tree* root, int value, int acc);
void get_node(tree* node, int key);
tree* simple_rotation(tree* root, int side);
tree* double_rotation(tree* root, int side);

int main(int argc, char const *argv[]) {
	
	tree* root, *tmp;
	int nums, value, action, buff, i, last_done, last_ask;
	
	last_done = 0;
	last_ask = 0;
	
	int haha = 0;
	
	scanf(" %d", &nums);
	
	for(i = 0; i < nums; i++) {
	    scanf(" %d %d", &action, &value);
	    
	    if(action == 1) {
	        root = insert(root, value);
	    }
	    
	    else {
	    	get_node(root, value);
	    }
	}

	return 0;
}



void get_node(tree* node, int key) {
	int total = 0;
	
	if(node == NULL) {
		printf("Data tidak ada\n");
		return;
	}
	
	total = node->pos;
	
	while(1) {
		if(node == NULL) {
			printf("Data tidak ada\n");
			return;
		}
		
		else if(node->key < key) { // right
			total += 1;
			node = node->right;
			if(node != NULL) {
				total += node->pos;
			}
		}
		
		else if(node->key > key) { // left
			total -= node->pos;
			node = node->left;
			
			if(node != NULL) {
				total += node->pos;
			}
		}
		
		else { // (node->key == key) { 
			// total += node->pos;
			printf("%d\n", total + 1);
			return;
		}
		
		
	}
	
}

tree* simple_rotation(tree* root, int side) {
	//printf("simple_rotation\n");

	tree* buff;

	// right
	if(side > 0) {
		buff = root->right;
		root->pos = buff->right->pos + 1;
		root->right = buff->left;
		buff->left = root;
		
	}
	// left
	else {
		buff = root->left;
		buff->pos = root->pos + 1;
		root->left = buff->right;
		buff->right = root;
	}

	// corrige o balance
	buff->balance = 0;
	root->balance = 0;

	return buff;
}

tree* double_rotation(tree* root, int side) {
	// printf("double_rotation\n");
	tree *a, *b, *buff;

	if( side > 0 ){ // right
		// Salva os ponteiros
		buff = root->right->left;
		a = root;
		b = root->right;
		
		// acerta o número de nós a esquerda
		buff->pos += a->pos + 1;
		if(buff->right != NULL) {
			b->pos = buff->right->pos;
		}
		else {
			b->pos = 0;
		}

		// Reestrutura a árvore
		a->right = buff->left;
		b->left = buff->right;
		buff->left = a;
		buff->right = b;

		// Verifica se o balance de root era +1 ou -1
		if(buff->balance > 0) {
			b->balance = 0;
			a->balance = -1;
		}
		else {
			b->balance = 1;
			a->balance = 0;	
		}
	}
	else { // at left
		// Salva os ponteiros
		buff = root->left->right; // nó c
		a = root;
		b = root->left;
		
		// acerta o número de nós a esquerda
		buff->pos += b->pos + 1;
		if(buff->right != NULL) {
			a->pos = buff->right->pos;	
		}
		else {
			a->pos = 0;
		}

		// Reestrutura a árvore
		a->left = buff->right;
		b->right = buff->left;
		buff->right = a;
		buff->left = b;

		// Verifica se o balance de root era +1 ou -1
		if(buff->balance > 0) {
			b->balance = -1;
			a->balance = 0;
		}
		else {
			b->balance = 0;
			a->balance = 1;	
		}
	}

	buff->balance = 0;

	return buff;
}

tree* insert(tree* root, int key) {

	int old_balance;

	if(root == NULL) {
		tree* node = malloc(sizeof(tree));
		node->balance = 0;
		node->key = key;
		node->left = NULL;
		node->right = NULL;
		node->pos = 0;
		return node;
	}

	if(root->key < key) { // adiciona a direita
		// se o filho era NULL adiciona a altura
		if(root->right == NULL) {
			root->balance++;
		}
		else {
			old_balance = root->right->balance;
		}

		root->right = insert(root->right, key);
		
		// Se mudou o balance e ele é diferente de zero rotacionar
		if(root->right->balance != old_balance && root->right->balance != 0) {
			root->balance++;
		}

		// Estourou a condição de AVL
		if(root->balance > 1) {
			// direita direita
			if(root->right->balance > 0) {
				return simple_rotation(root, 1);
			}
			// direita esquerda
			if(root->right->balance < 0) {
				return double_rotation(root, 1);
			}
		}
		
	}
	else { // adicionando a esquerda
		
		root->pos++;
		
		// se o filho era NULL adiciona a altura
		if(root->left == NULL) {
			root->balance--;
		}
		else {
			old_balance = root->left->balance;
		}

		root->left = insert(root->left, key);

		// Se mudou o balance e ele é diferente de zero rotacionar
		if(root->left->balance != old_balance && root->left->balance != 0) {
			root->balance--;
		}

		// Estourou a condição de AVL
		if(root->balance < -1) {
			// esquerda esquerda
			if(root->left->balance < 0) {
				return simple_rotation(root, -1);
			}
			// esquerda direita
			if(root->left->balance > 0) {
				return double_rotation(root, -1);
			}
		}
	}

	return root;
}
