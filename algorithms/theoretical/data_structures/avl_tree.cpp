// TODO: Build a remove function where the nodes don't now about the fathers
// TODO: AVL Tree Adition method

#include <bits/stdc++.h>

#define SIZE 10

class node {
private:
node *left;
node *right;
int value;
int balance;

public:

	node(int value){
		this->left = NULL;
		this->right = NULL;
		this->value = value;
		this->balance = 0;
	}
	
	int get_value() {
		return this->value;
	}
	void set_value(int value) {
		this->value = value;
	}
	
	node *get_left() {
		return this->left;
	}
	
	node *get_right() {
		return this->right;
	}
	
	void set_left(node *element) {
		this->left = element;
	}
	
	void set_right(node *element) {
		this->right = element;
	}

	int get_balance() {
		return this->balance;
	}

	void grow_balance() {
		this->balance++;
	}

	void drop_balance() {
		this->balance--;
	}
	
	void set_balance(int balance) {
		this->balance = balance;
	}
	
};

class tree {
private:
	node *root; 
	
	// Here the argument is the node itself
	node* simple_rotation(node *el, int side) {
		node *clone;
		
		printf("simple rotation!\n");
		
		if(side == -1) { // Left subtree
			clone = el->get_left(); // Saves the pointer
			el->set_left(clone->get_right()); // Make the node points to him's son's son.
			clone->set_right(el); // Make him's son points to him
		}
		
		else if(side == 1) { // Right subtree
			clone = el->get_right(); // Saves the pointer
			el->set_right(clone->get_left()); // Make the node points to him's son's son.
			clone->set_left(el); // Make him's son points to him
		}
		
		// Correct the balances
		el->set_balance(0); 
		clone->set_balance(0);
		
		return clone;
	}

	node* double_rotation(node *el, int side) {
		node *clone, *sub_tree_a, *sub_tree_b, *node_a, *node_b;
		
		printf("double rotation! %d\n", el->get_value());
		
		if(side == -1) { // Left subtree
			
			// Save every pointer in a easier name
			clone = el->get_left()->get_right(); // Saves the pointer
			sub_tree_a = clone->get_right();
			sub_tree_b = clone->get_left();
			node_a = el;
			node_b = el->get_left();

			// Make the new root get it's new children
			clone->set_right(node_a);
			clone->set_left(node_b);

			node_b->set_right(sub_tree_b);
			node_a->set_left(sub_tree_a);

			// Correct the balances
			if(clone->get_balance() > 0) {
				node_a->set_balance(0);
				node_b->set_balance(-1);
			}
			else if(clone->get_balance() < 0) {
				node_a->set_balance(1);
				node_b->set_balance(0);
			}
			
		}
		
		else if(side == 1) { // Right subtree
			// Save every pointer in a easier name
			clone = el->get_right()->get_left(); // Saves the pointer
			sub_tree_a = clone->get_left();
			sub_tree_b = clone->get_right();
			node_a = el;
			node_b = el->get_right();

			// Make the new root get it's new children
			clone->set_left(node_a);
			clone->set_right(node_b);

			node_b->set_left(sub_tree_b);
			node_a->set_right(sub_tree_a);

			// Correct the balances
			if(clone->get_balance() > 0) {
				node_a->set_balance(-1);
				node_b->set_balance(0);
			}
			else if(clone->get_balance() < 0) {
				node_a->set_balance(0);
				node_b->set_balance(1);
			}
		}
		
		// Correct the balances
		clone->set_balance(0);
		
		return clone;
	}
	
	// TODO: verify how to add balance correctly
	node* add(int value, node *el) { 
		node *ret;
		int child_balance; // Added to child
		int old_balance; // Compare if the node height really changed
		
		// Values that we want to add at the right
		if(el->get_value() < value) {

			// Added node in the leaf, there's no way to the tree break the AVL property in this node
			if(el->get_right() == NULL) {
				el->set_right(new node(value));
				el->grow_balance();

				printf("node: %d | balance: %d\n", el->get_right()->get_value(), el->get_right()->get_balance());
				printf("node: %d | balance: %d\n", el->get_value(), el->get_balance());
				
				return el;
			}

			old_balance = el->get_right()->get_balance();
			ret = this->add(value, el->get_right());
			
			child_balance = ret->get_balance();

			if(child_balance != 0 && old_balance != child_balance) {
				el->grow_balance(); // Verify if the height of the tree has grown
			}

			// Right Right
			if(el->get_balance() > 1 && ret->get_balance() > 0) {
				ret = simple_rotation(el, 1);
				return ret;
			}

			// Right Left
			else if(el->get_balance() > 1 && ret->get_balance() < 0) {
				ret = double_rotation(el, 1);
				return ret;
			}

			el->set_right(ret);
			
		}
		
		else {
			
			// Added node in the leaf, there's no way to the tree break the AVL property in this node
			if(el->get_left() == NULL) {
				el->set_left(new node(value));
				el->drop_balance();
				
				printf("node: %d | balance: %d\n", el->get_left()->get_value(), el->get_left()->get_balance());
				printf("node: %d | balance: %d\n", el->get_value(), el->get_balance());
				
				return el;
			}

			old_balance = el->get_left()->get_balance();
			
			ret = this->add(value, el->get_left());
			
			child_balance = ret->get_balance();

			if(child_balance != 0 && old_balance != child_balance) {
				el->drop_balance(); // Verify if the height of the tree has grown
			} 

			// Left Left
			if(el->get_balance() < -1 && ret->get_balance() < 0) {
				ret = simple_rotation(el, -1);
				return ret;
			}

			// Left Right
			else if(el->get_balance() < -1 && ret->get_balance() > 0) {
				ret = double_rotation(el, -1);
				return ret;
			}

			// Set the child where it should be
			el->set_left(ret);
			
		}
		
		printf("node: %d | balance: %d\n", el->get_value(), el->get_balance());
		
		return el;
	}
	
	
	void print_order(node *el) {
		if(el == NULL) return;
		
		this->print_order(el->get_left());
		//printf("%d ", el->get_value());
		printf("%d (%d) | ", el->get_value(), el->get_balance());
		this->print_order(el->get_right());
	}
	
	void print_pre_order(node *el) {
		if(el == NULL) return;
		
		//printf("%d ", el->get_value());
		printf("%d (%d) | ", el->get_value(), el->get_balance());
		this->print_pre_order(el->get_left());
		this->print_pre_order(el->get_right());
	}
	
	void print_pos_order(node *el) {
		if(el == NULL) return;
		
		this->print_pre_order(el->get_left());
		this->print_pre_order(el->get_right());
		//printf("%d ", el->get_value());
		printf("%d (%d) | ", el->get_value(), el->get_balance());
	}
	
	node *find(int value, node *el) {
		// The node isn't in the tree
		if(el == NULL) {
			return NULL;
		}
		
		// Found the node
		if(el->get_value() == value) {
			return el;
		}
		
		if(el->get_value() < value) {
			return this->find(value, el->get_right());
		}
		
		return this->find(value, el->get_left());
		
	}
	
	
	// TODO: Build a remove function where the nodes don't now about the fathers
	/**
	 *  1 -> success
	 * -1 -> nothing to remove
	 */
	node* rm_node(int value, node *el) {
		
		if(el == NULL){
			return NULL; // Error removing the element
		}

		// Return to the father the new addres to point to
		if(el->get_value() == value) {
			
			// Leaf node
			if(el->get_left() == NULL && el->get_right() == NULL) {
				delete el;
				return NULL;
			}
			
			// One child at left
			else if(el->get_left() != NULL && el->get_right() == NULL) {
				node *temp = el->get_left();
				delete el;
				return temp;
			}
			
			// One child at right
			else if(el->get_left() == NULL && el->get_right() != NULL) {
				node *temp = el->get_right();
				delete el;
				return temp;
			}
			
			// Two childs
			else {
				// Find the biggest element in the subtree at left
				node *buff = el->get_left(), *father = el;
				int myval = el->get_value();
				
				while(buff->get_right() != NULL) {
					father = buff;
					buff = buff->get_right();
				}
				
				// Swap both of them
				el->set_value(buff->get_value());
				buff->set_value(myval);
				
				// remove the element
				if(father == el) { // Check if we have more than one node at the subtree at left
					father->set_left(NULL);
				}
				else {
					father->set_right(NULL);
				}
				
				delete buff;
				
				return el; 
			}
			
		}
		
		// Keep looking for the node
		else {
			node* buff;
			if(el->get_value() < value) {
				buff = rm_node(value, el->get_right());
				el->set_right(buff);
			}
			else {
				buff = rm_node(value, el->get_left());
				el->set_left(buff);
			}
			
			return el;
			
		}
		
	}
	

public:

	tree() {
		this->root = NULL;
	}
	
	~tree() {
		
	}
	
	
	node* add(int value) {
		
		if(this->root == NULL ) {
			root = new node(value);
			return this->root;
		}

		this->root = this->add(value, this->root);


	}
	
	
	void print_order() {
		
		if(this->root == NULL) {
			printf("Empty tree\n");
			return;
		}
		
		this->print_order(this->root);
		printf("\n");
	}
	
	void print_pre_order() {
		
		if(this->root == NULL) {
			printf("Empty tree\n");
			return;
		}
		
		this->print_pre_order(this->root);
		printf("\n");
	}
	
	void print_pos_order() {
		
		if(this->root == NULL) {
			printf("Empty tree\n");
			return;
		}
		
		this->print_pos_order(this->root);
		printf("\n");
	}
	
	
	node *find(int value) {
		this->find(value, this->root);
	}
	
	node *rm_node(int value) {
		node* buff = this->rm_node(value, this->root);
		this->root = buff;
		return this->root;
	}
};


int main() {
	
	int arr[SIZE];
	
	tree *a = new tree(), *c = new tree();
	node *b;
	
	// Obs: Erro na adição do valor 68
	
	for(int i = 0; i < SIZE; i++) {
		scanf(" %d", arr + i);
		a->add(arr[i]);
		printf("\n");
		//c->add(arr[i]);
	}
	
	// Test of order print
	a->print_order();
	a->print_pre_order();
	a->print_pos_order();
	
	// Test of element find
	b = a->find(56);
	if(b != NULL) 
		printf("Found %d at %ld\n", b->get_value(), (long) b);
	else{
		printf("Node not found\n");
	}
	
	// Test of element deletion
	c->add(8);
	c->add(4);
	c->add(5);
	c->add(10);
	c->add(12);
	
	c->print_order();
	c->print_pre_order();
	c->print_pos_order();
	c->rm_node(8);
	printf("\n");
	c->print_order();
	c->print_pre_order();
	c->print_pos_order();
	c->rm_node(100);
	printf("\n");
	c->print_order();
	c->print_pre_order();
	c->print_pos_order();
	
	
	return 0;
}