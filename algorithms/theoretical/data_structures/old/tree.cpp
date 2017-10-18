// TODO: Build a remove function where the nodes don't now about the fathers
// TODO: AVL Tree Adition method

#include <bits/stdc++.h>

#define SIZE 10

class node {
private:
node *left;
node *right;
int value;

public:

    node(int value){
        this->left = NULL;
        this->right = NULL;
        this->value = value;
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
    
};

class tree {
private:
    node *root;
    
    
    void add(int value, node *el) {
        
        // Values that we want to add at the right
        if(el->get_value() < value) {
            // Ready to add
            if(el->get_right() == NULL) {
                el->set_right(new node(value));
                return;
            }
            this->add(value, el->get_right());
        }
        
        else {
            if(el->get_left() == NULL) {
                el->set_left(new node(value));
                return;
            }
            this->add(value, el->get_left());
        }
        
    }
    
    
    void print_order(node *el) {
        if(el == NULL) return;
        
        this->print_order(el->get_left());
        printf("%d ", el->get_value());
        this->print_order(el->get_right());
    }
    
    void print_pre_order(node *el) {
        if(el == NULL) return;
        
        printf("%d ", el->get_value());
        this->print_pre_order(el->get_left());
        this->print_pre_order(el->get_right());
    }
    
    void print_pos_order(node *el) {
        if(el == NULL) return;
        
        this->print_pre_order(el->get_left());
        this->print_pre_order(el->get_right());
        printf("%d ", el->get_value());
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
        
        // printf("at: %d\n", el->get_value());
        
        
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
    
    
    void add(int value) {
        if(this->root == NULL ) {
            root = new node(value);
            return;
        }
        this->add(value, this->root);
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
    
    for(int i = 0; i < SIZE; i++) {
        scanf(" %d", arr + i);
        a->add(arr[i]);
        //c->add(arr[i]);
    }
    
    // Test of order print
    a->print_order();
    a->print_pre_order();
    a->print_pos_order();
    
    // Test of element find
    b = a->find(56);
    printf("found %d at %ld\n", b->get_value(), (long) b);
    
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