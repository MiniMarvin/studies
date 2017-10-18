#include <bits/stdc++.h>

using namespace std;

class nd {
public:
	nd *dad;
	int key;

	nd(int key) {
		this->key = key;
		this->dad = NULL;
	}
};

class stck{
public:
	nd *top;

	stck() {
		this->top = NULL;
	}

	void add(int key) {
		if(top == NULL){
			this->top = new nd(key);
		}
		else {
			nd *el = new nd(key);
			el->dad = this->top;
			this->top = el;
		}
	}

	void print() {
		while(this->top != NULL) {
			printf("%d\n", this->top->key);
			this->top = this->top->dad;
		}
	}
};

int main() {

	stck *a = new stck();

	a->add(10);
	a->add(20);
	a->add(30);
	a->add(40);
	a->add(50);
	a->add(60);
	a->add(70);
	a->add(80);
	a->add(90);

	a->print();

	return 0;
}