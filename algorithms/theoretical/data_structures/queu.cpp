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
	nd *st;

	stck() {
		this->st = NULL;
	}

	void add(int key) {
		if(st == NULL){
			this->st = new nd(key);
		}
		else {
			nd *el = this->st;
			
			while(el->dad != NULL) {
				el = el->dad;
			}
			el->dad = new nd(key);
			// this->st = el;
		}
	}

	void print() {
		while(this->st != NULL) {
			printf("%d\n", this->st->key);
			this->st = this->st->dad;
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