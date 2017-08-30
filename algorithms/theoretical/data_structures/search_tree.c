// Implementação de Árvore binária em C
#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
	int balance;
	int key;
	struct tree* left;
	struct tree* right;
} tree;

// Prototypes
tree* insert(tree* root, int key); 
void print_preorder(tree* root);
void print_inorder(tree* root);
void print_posorder(tree* root);
tree *delete(tree* root, int key);

int main(int argc, char const *argv[]) {
	
	tree* root;
	int buff;

	for(int i = 0; i < 10; i++) {
		scanf(" %d", &buff);
		root = insert(root, buff);
	}

	print_preorder(root);
	printf("\n");

	root = delete(root, -1);
	root = delete(root, 62);
	root = delete(root, 35);

	print_preorder(root);
	printf("\n");	

	return 0;
}


tree* simple_rotation(tree* root, int side){
	printf("simple_rotation\n");

	tree* buff;

	// right
	if(side > 0) {
		buff = root->right;
		root->right = buff->left;
		buff->left = root;
	}
	// left
	else {
		buff = root->left;
		root->left = buff->right;
		buff->right = root;
	}

	// corrige o balance
	buff->balance = 0;
	root->balance = 0;

	return buff;
}

tree* double_rotation(tree* root, int side){
	printf("double_rotation\n");
	tree *a, *b, *buff;

	if( side > 0 ){ // right
		// Salva os ponteiros
		buff = root->right->left;
		a = root;
		b = root->right;

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
	else{
		// Salva os ponteiros
		buff = root->left->right;
		a = root;
		b = root->left;

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
		return node;
	}

	if(root->key < key) {
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
	else {
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

void print_preorder(tree* root) {
	if(root == NULL) {
		return;
	}

	printf("%d ", root->key);
	print_preorder(root->left);
	print_preorder(root->right);
}

void print_inorder(tree* root) {
	if(root == NULL) {
		return;
	}

	print_inorder(root->left);
	printf("%d ", root->key);
	print_inorder(root->right);
}

void print_posorder(tree* root) {
	if(root == NULL) {
		return;
	}

	print_posorder(root->left);
	print_posorder(root->right);
	printf("%d ", root->key);
}

tree *delete(tree* root, int key) {
	tree *buff, *father;

	if(root == NULL) {
		printf("Node not found!\n");
		return root;
	}

	if(root->key == key) {
		if(root->right != NULL && root->left != NULL) {
			
			father = root;
			buff = root->right;

			while(buff->left != NULL) {
				father = buff;
				buff = buff->left;
			}

			root->key = buff->key;
			father->left = buff->right;
			free(buff);
			
		}
		else if(root->right == NULL && root->left != NULL) {
			buff = root->left;
			free(root);
			root = buff;
		}
		else if(root->right != NULL && root->left == NULL) {
			buff = root->right;
			free(root);
			root = buff;
		}
		else {
			free(root);
			root = NULL;
		}
		printf("deleted!\n");
	}

	else if(root->key < key) {
		root->right = delete(root->right, key);
	}
	else {
		root->left = delete(root->left, key);
	}

	return root;
}