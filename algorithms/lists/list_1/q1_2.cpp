#include <iostream>

using namespace std;

class node {
private:
	node *next;
	long int value;

public:
	node(long int value) {
		this->next = NULL;
		this->value = value;
	}

	long int get_val() {
		return this->value;
	}

	node* get_next() {
		return this->next;
	}

	void set_next(node *element) {
		this->next = element;
	}
};

class queue {
private:
	node *head;
public:

	queue() {
		this->head = NULL;
	}

	void add(long int value) {

		if(this->head == NULL) {
			this->head = new node(value);
			return;
		}

		node *buff = this->head;

		while( buff->get_next() != NULL) {
		    buff = buff->get_next();
		}

		buff->set_next( new node(value) );
	}

	void remove() {
		if(this->head != NULL){
			node *clone = this->head;
			this->head = this->head->get_next();	
			delete clone;
		}
	}

	long int get_first(){
		return head->get_val();
	}

	void print_first() {
		if(this->head == NULL) {
			cout << "Empty!" << endl;
			return;
		}

		cout << this->head->get_val() << endl;
	}

};	

int main() {

	queue *lista = new queue();
	int in_num, action;
	long int value;

	cin >> in_num;

	for (int i = 0; i < in_num; ++i) {
		cin >> action;
		if(action == 1) {
			cin >> value;
			lista->add(value);
		}
		else if(action == 2) {
			lista->remove();
		}
		else {
			lista->print_first();
		}
	}


	return 0;
}