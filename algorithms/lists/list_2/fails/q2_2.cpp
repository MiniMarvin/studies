// TODO: Build a remove function where the nodes don't now about the fathers
// TODO: AVL Tree Adition method

#include <bits/stdc++.h>


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
		
		//printf("simple rotation!\n");
		
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
		
		//printf("double rotation! %d\n", el->get_value());
		
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

				// printf("node: %d | balance: %d\n", el->get_right()->get_value(), el->get_right()->get_balance());
				// printf("node: %d | balance: %d\n", el->get_value(), el->get_balance());
				
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
				
				// printf("node: %d | balance: %d\n", el->get_left()->get_value(), el->get_left()->get_balance());
				// printf("node: %d | balance: %d\n", el->get_value(), el->get_balance());
				
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
		
		// printf("node: %d | balance: %d\n", el->get_value(), el->get_balance());
		
		return el;
	}
	
	
	int get_pos(node *el, int key, int acc) {
		// end of subtree
		if(el == NULL) 
			return -1;
		
		int result = this->get_pos(el->get_left(), key, acc);
		
		// already found
		if(result == -2) {
			return -2;
		}
		
		if(result != -1) {
			acc = result + 1;
		}
		
		// In order ----------------------------------------------------------------//
	    // Found the value
		if(el->get_value() == key) {
		    printf("%d\n", acc);
		    return -2;
		}
	    //--------------------------------------------------------------------------//
		
		result = this->get_pos(el->get_right(), key, acc);
	
		// found the value
		if(result == -2) {
		    return -2;
		}
		
		// didn't found, but son wasn't NULL actualize the acc
		else if(result != -1) {
	        acc = result + 1;
		}
		
		return acc;
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
	
	
	int get_pos(int key) {
		
		if(this->root == NULL) {
			return -2;
		}
		
		int back = this->get_pos(this->root, key, 1);
		
		if( back != -2 ) { // didn't found
			printf("Data tidak ada\n");
		}
	}
	
};


int main() {
	
	//int arr[SIZE];
	int action, value;
	tree *a = new tree(), *c = new tree();
	node *b;
	
	int len;
	scanf(" %d", &len);
	
	for(int i = 0; i < len; i++) {
		
		scanf(" %d %d", &action, &value);
		if(action == 1) {
			a->add(value);
		}
		else {
			a->get_pos(value);
		}
		
	}
	return 0;
}