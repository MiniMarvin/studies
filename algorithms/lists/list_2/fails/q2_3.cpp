// Implementação de Árvore binária em C
#include <bits/stdc++.h>

using namespace std;

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
	int nums, value, action, buff, i, last_done = 0, last_ask;
	
	cin >> nums;
	
	for(i = 0; i < nums; i++) {
	    //scanf(" %d %d", &action, &value);
	    cin >> action;
	    cin >> value;
	    
	    if(action == 1) {
	        root = insert(root, value);
	        last_done = 0;
	    }
	    
	    else {
	    	
	        if(last_done == 1 && last_ask <= value) get_node(root, value);
	        
	        else if(last_done == -1) get_node(root, value); // had to see the entire tree
	        
	        else {
	        	
	        	last_ask = value;
		        last_done = 1;
		        
		        buff = find_pos(root, value, 1); // original acc = 1
		        
		        if(buff != -2) { // didn't found
		            printf("Data tidak ada\n");
		            last_done = -1;
		        }
		        
		        
	        }
	    }
	}

	return 0;
}


/****
 * Pass to the accumulator the number of the call and add the tree height to the acc every time that it returns
 * return -1 in NULL
 * return it's acc in not found
 * return -2 in found
 * every time that returns a value that is bigger than 0 substitute it in the accumulator
 ****/

int find_pos(tree* root, int value, int acc) {
    
    int result;
    
    if(root == NULL) {
		return -1;
	}
	
	result = find_pos(root->left, value, acc);
	
	// found the value
	if(result == -2) {
	    return -2;
	}
	// didn't found, but son wasn't NULL actualize the acc
	else if(result != -1) {
        acc = result + 1;
	}
	
	root->pos = acc;
    
    // In order ----------------------------------------------------------------//
    // Found the value
	if(root->key == value) {
	    printf("%d\n", acc);
	    return -2;
	}
    //--------------------------------------------------------------------------//
    
	result = find_pos(root->right, value, acc);
	
	// found the value
	if(result == -2) {
	    return -2;
	}
	
	// didn't found, but son wasn't NULL actualize the acc
	else if(result != -1) {
        acc = result + 1;
	}
	
	root->pos = acc;
	
	return acc;
}

void get_node(tree* node, int key) {
	if(node == NULL) {
		printf("Data tidak ada\n");
	}
	
	while(1) {
		if(node == NULL) {
			printf("Data tidak ada\n");
			return;
		}
		else if(node->key == key) {
			printf("%d\n", node->pos);
			return;
		}
		else if(node->key < key) {
			node = node->right;
		}
		else{
			node = node->left;
		}
	}
	
}

tree* simple_rotation(tree* root, int side) {
	//printf("simple_rotation\n");

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

tree* double_rotation(tree* root, int side) {
	// printf("double_rotation\n");
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
		tree* node = new tree;
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
