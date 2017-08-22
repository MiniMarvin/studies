#include <iostream>
#include <cstdlib>

using namespace std;

/**
 * @brief      Class for tree node.
 */
class tree_node{
private:
	tree_node *left;
	tree_node *right;
	int data;

public:

	/**
	 * @brief      The node constructor, generate it as a leaf.
	 *
	 * @param[in]  data  The data to be added in the leaf
	 */
	tree_node(int data) {
		this->left = NULL;
		this->right = NULL;
		this->data = data;
	}
	~tree_node(){}

	/**
	 * @brief      Gets the left node.
	 *
	 * @return     The left node.
	 */
	tree_node* get_left() {
		return this->left; 
	}

	/**
	 * @brief      Gets the right node.
	 *
	 * @return     The right node.
	 */
	tree_node* get_right() {
		return this->right;
	}

	/**
	 * @brief      Puts a node in left.
	 *
	 * @param[in]  value  The value to be added.
	 */
	void put_left(int value) {
		this->left = new tree_node(value);
	}

	/**
	 * @brief      Puts a node at right.
	 *
	 * @param[in]  value  The value to be added
	 */
	void put_right(int value) {
		this->right = new tree_node(value);
	}

	/**
	 * @brief      Sets the left pointer into a certain node.
	 *
	 * @param      element  The element to be insert.
	 */
	void set_left(tree_node* element) {
		this->left = element;
	}

	/**
	 * @brief      Sets the right pointer into a cerntain node.
	 *
	 * @param      element  The element to be insert.
	 */
	void set_right(tree_node* element) {
		this->right = element;
	}

	/**
	 * @brief      Sets the value of the node.
	 *
	 * @param[in]  value  The value to be placed.
	 */
	void set_value(int value) {
		this->data = value;
	}

	/**
	 * @brief      Gets the value of the node.
	 *
	 * @return     The value.
	 */
	int get_value() {
		return this->data;
	}

	void right_null(){
		this->right = NULL;
	}

	void left_null(){
		this->left = NULL;
	}
};

/**
 * @brief      Class for binary search tree.
 */
class tree {

private:
	tree_node *head; ///< The tree head/root.

	/**
	 * @brief      Print the tree in order recursively.
	 *
	 * @param      element  The element
	 */
	void print_order(tree_node* element) {
		
		if(element == NULL) {
			return;
		}

		print_order(element->get_left());
		cout << element->get_value() << " ";
		print_order(element->get_right());

	}

	/**
	 * @brief      Print the tree in pre-order recursively.
	 *
	 * @param      element  The element
	 */
	void print_preorder(tree_node* element) {
		
		if(element == NULL) {
			return;
		}

		cout << element->get_value() << " ";
		print_preorder(element->get_left());
		print_preorder(element->get_right());

	}

	/**
	 * @brief      Print the tree in pos-order recursively.
	 *
	 * @param      element  The element
	 */
	void print_posorder(tree_node* element) {
		
		if(element == NULL) {
			return;
		}

		print_posorder(element->get_left());
		print_posorder(element->get_right());
		cout << element->get_value() << " ";

	}

public:
	/**
	 * @brief      Tree Constructor.
	 */
	tree() {
		this->head = NULL;
	}
	~tree(){}

	/**
	 * @brief      Removes a node from the tree.
	 *
	 * @param[in]  value  The value of the node that is been search.
	 */
	void remove_node(int value) {
		// TODO: find a way to find it's father (recursive: return the son value)
		// Find the node to remove
		tree_node *element, *father;

		father = element = this->head;

		// Busca pelo nó e pelo pai dele ------------------------------------------//
		// Follow the path of the tree order untill find a node with the wanted value
		while(element != NULL && element->get_value() != value ) {
			father = element;
			if(element->get_value() < value) {
				element = element->get_right();
			}
			else {
				element = element->get_left();
			}
		}

		//-------------------------------------------------------------------------//
		// Check if the found node really did exist
		if(element == NULL) {
			cout << "nothing has been done" << endl;
			return;
		}

		// Leaf node
		else if(element->get_left() == NULL &&  element->get_right() == NULL) {
			if(element->get_value() > father->get_value()) {
				father->set_left(NULL);
				father->left_null();
			}
			else {
				father->set_right(NULL);
				father->right_null();
			}

			cout << "deleted leaf" << endl;
			free(element);
		}

		// The node has at least one child
		else if(element->get_right() != NULL || element->get_left() != NULL) {
			
			tree_node *buff, *buff_father;

			if(element->get_left() != NULL && element->get_right() == NULL) { // The children node is at left
				
				buff = element->get_left();

				if(father->get_value() < element->get_value()) {
					father->set_left(element->get_left());
					delete element;
					cout << "deleted" << endl;
				}
				else {
					father->set_right(element->get_left());
					delete element;
					cout << "deleted" << endl;	
				}
			}

			else if(element->get_left() == NULL && element->get_right() != NULL){ // The children node is at left
				
				buff = element->get_right();

				if(father->get_value() < element->get_value()) {
					father->set_left(element->get_right());
					delete element;
					cout << "deleted" << endl;
				}
				else {
					father->set_right(element->get_right());
					delete element;
					cout << "deleted" << endl;	
				}
			}

			// The node has two children
			else {
				// search for the biggest element at left
				buff = element->get_left();
				buff_father = element->get_left();

				while(buff->get_right() != NULL) {
					buff_father = buff;
					buff = buff->get_right();					
				}

				// Swap the nodes values
				int cp = element->get_value();
				element->set_value(buff->get_value());
				buff->set_value(cp);

				// Remove the end node
				remove_node(buff, buff_father);

			}
		}

	}

	/**
	 * @brief      Removes a node from the tree.
	 *
	 * @param[in]  value  The value of the node that is been search.
	 */
	void remove_node(tree_node *element, tree_node *father) {
		// TODO: find a way to find it's father (recursive: return the son value)
		// Find the node to remove
		tree_node *buff_father;

		// Check if the found node really did exist
		if(element == NULL){
			return;
		}

		// Leaf node
		else if(element->get_left() == NULL &&  element->get_right() == NULL) {
			delete element;
		}

		// The node has at least one child
		else if(element->get_right() != NULL || element->get_left() != NULL) {
			
			tree_node* buff;

			if(element->get_left() != NULL && element->get_right() == NULL) { // The children node is at left
				
				buff = element->get_left();

				if(father->get_value() < element->get_value()) {
					father->set_left(element->get_left());
					delete element;
					cout << "deleted" << endl;
				}
				else {
					father->set_right(element->get_left());
					delete element;
					cout << "deleted" << endl;	
				}
			}

			else if(element->get_left() == NULL && element->get_right() != NULL){ // The children node is at left
				
				buff = element->get_right();

				if(father->get_value() < element->get_value()) {
					father->set_left(element->get_right());
					delete element;
					cout << "deleted" << endl;
				}
				else {
					father->set_right(element->get_right());
					delete element;
					cout << "deleted" << endl;	
				}
			}

			// The node has two children
			else {
				// search for the biggest element at left
				buff = element->get_left();


				while(buff->get_right() != NULL) {
					buff = buff->get_right();					
				}

				int cp = element->get_value();
				element->set_value(buff->get_value());

				remove_node(buff, buff_father);

			}
		}

	}

	/**
	 * @brief      Find a node with a specific value in the tree.
	 *
	 * @param[in]  value  The value of the node.
	 *
	 * @return     The node found.
	 */
	tree_node *find(int value){
		tree_node *element = this->head;

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

	/**
	 * @brief      Get the head of the tree.
	 *
	 * @return     The head.
	 */
	tree_node *get_head() {
		return this->head;
	}

	/**
	 * @brief      Add a value in a simple search tree
	 *
	 * @param[in]  value  The value to be added
	 */
	void add(int value) {
		if(this->head == NULL ) {
			this->head = new tree_node(value);
		}
		else {
			tree_node* clone = this->head;

			while(clone != NULL) {
				
				if(clone->get_value() > value) {
					if(clone->get_left() == NULL) {
						clone->set_left(new tree_node(value));
						break;
					}
					else{
						clone = clone->get_left();
					}
				}

				else {
					if(clone->get_right() == NULL) {
						clone->set_right(new tree_node(value));
						break;
					}

					else{
						clone = clone->get_right();
					}
				}

			}

		}
	}

	/**
	 * @brief      Print the tree in order using a private function.
	 */
	void print_order() {
		this->print_order(this->head);
		cout << endl;
	}

	/**
	 * @brief      Print the tree in pre-order using a private function.
	 */
	void print_preorder() {
		this->print_preorder(this->head);
		cout << endl;
	}

	/**
	 * @brief      Print the tree in pos-order using a private function.
	 */
	void print_posorder() {
		this->print_posorder(this->head);
		cout << endl;
	}


};


void print_arr(int *arr, int size);


int main(int argc, char const *argv[]) {
	
	tree *a = new tree();
	int arr[10];

	srand(time(NULL));

	for (int i = 0; i < 10; ++i) {
		arr[i] = rand()%100;
		a->add(arr[i]);
	}

	tree_node* found = a->find(-20);
	if(found != NULL) cout << found->get_value() << endl;
	else cout << "NULL" << endl;

	print_arr(arr, 10);

	cout << endl;

	cout << "order:     ";
	a->print_order();
	cout << "pre-order: ";
	a->print_preorder();
	cout << "pos-order: ";
	a->print_posorder();

	a->remove_node(arr[9]);

	cout << endl;

	cout << "order:     ";
	a->print_order();
	cout << "pre-order: ";
	a->print_preorder();
	cout << "pos-order: ";
	a->print_posorder();

	return 0;
}

void print_arr(int *arr, int size) {
	for (int i = 0; i < size; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}