#include <bits/stdc++.h>

using namespace std;

class node {
public:
    int key;
    node *left;
    node *right;
    
    node(int key) {
        this->key = key;
        this->left = NULL;
        this->right = NULL;
    }
};

class bst {
    
private:
    node *add(node *el, int key) {
        if(el == NULL) {
            return new node(key);
        }
        
        if(key < el->key) {
            el->left = add(el->left, key);
        }
        else {
            el->right = add(el->right, key);
        }
        
        return el;
    }
    
    void pre_order(node *el) {
        if(el == NULL) {
            return;
        }
        
        cout << el->key << " ";
        pre_order(el->left);
        pre_order(el->right);
    }
    
    int e_dist(node *el, int h) {
        if(el == NULL) return 0;
        if(el->right == NULL && el->left == NULL) {
            return h;
        }
        
        int b = 0;
        b += e_dist(el->left, h + 1);
        b += e_dist(el->right, h + 1);
        return b;
    }
    
    
public:
    node *root;
    
    bst() {
        this->root = NULL;
    }
    
    void add(int key) {
        this->root = this->add(this->root, key);
    }
    
    node *find(int key) {
        
    }
    
    void pre_order() {
        pre_order(this->root);
        cout << endl;
    }
    
    int e_dist() {
        return this->e_dist(this->root, 0);
    }
    
};


int main() {
    bst *a = new bst();
    a->add(12);
    a->add(21);
    a->add(14);
    a->add(30);
    a->add(8);
    a->add(5);
    a->add(9);
    a->add(100);
    a->add(28);
    
    a->pre_order();
    
    cout << a->e_dist() << endl;
    
    return 0;
}