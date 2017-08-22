#include <iostream>

using namespace std;

class tree_node{
private:
	tree_node *left;
	tree_node *right;
	int data;

public:

	tree_node(int data) {
		this->left = NULL;
		this->right = NULL;
		this->data = data;
	}

	tree_node* get_left() {
		return this->left; 
	}

	tree_node* get_right() {
		return this->right;
	}

	void put_left(int value) {
		this->left = new tree_node(value);
	}

	void put_right(int value) {
		this->right = new tree_node(value);
	}

	void set_left(tree_node* element) {
		this->left = element;
	}

	void set_right(tree_node* element) {
		this->right = element;
	}

	void set_value(int value) {
		this->data = value;
	}

	int get_value() {
		return this->data;
	}
};

class tree {
private:
	tree_node *head;

public:
	tree() {
		this->head = NULL;
	}

	void remove_node(int value) {
		tree_node *element = head;
		
		
	}

	tree_node *find(int value){
		tree_node *element = head;

		// Follow the path of the tree order untill find a node with the wanted value
		while(element != NULL && element->get_value() != value ) {
			if(element->get_value() < value) {
				element = element->get_right();
			}
			else {
				element = element->get_left();
			}
		}

		return element;
	}

	tree_node *recursive_find(int value, tree_node *element){

		// Follow the path of the tree order untill find a node with the wanted value
		if(element != NULL && element->get_value() != value) {
			if(element->get_value() < value) {
				element = recursive_find(value, element->get_left());
			}
			else {
				element = recursive_find(value, element->get_right());
			}
		}

		return element;
	}

	tree_node *get_head() {
		return this->head;
	}

};

int main(int argc, char const *argv[]) {
	/* code */
	return 0;
}