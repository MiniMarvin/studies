#include <iostream>


class node {

private:
    node *left;
    node *right;
    int value;
public:

    node(int value) {
        this->left = NULL; 
        this->right = NULL;
        this->value = value;
    }

    void set_right(node *element) {
        this->right = element;
    }
    
    void set_left(node *element) {
        this->right = element;
    }
    
    node* get_left() {
        return this->left;
    }
    
    node* get_right() {
        return this->right;
    }

    int get_value() {
        return this->value;
    }
    
    void set_value(int value) {
        this->value = value;
    }

}

class tree{

private:
    node* head;
    
public:
    tree() {
        this->head = NULL;
    }
    
    void add_element(int value) {
        if(this->head == NULL) {
            this->head = new node(value);
        }
        else {
            
        }
    }
    
}

int main() {
    return 0;
}