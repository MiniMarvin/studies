// TODO: Build a remove function where the nodes don't now about the fathers

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
    int rm_node(int value, node *el, node *father) {
        
        printf("at: %d\n", el->get_value());
        
        if(el == NULL){
            return -1; // Error removing the element
        }
        
        // Execute the remotion procedure
        if(el->get_value() == value) {
            
            // Leaf node
            if(el->get_left() == NULL && el->get_right() == NULL) {
                if(father == NULL) { // If the remotion is made in root
                    delete el;
                    this->root = NULL;
                }
                else{
                    
                    delete el;
                    
                    // Remove reference to the deleted node
                    if(father->get_value() < value) {
                        father->set_right(NULL);
                    }
                    else {
                        father->set_left(NULL);
                    }
                    
                }
            }
            
            // one child at right
            else if(el->get_left() == NULL && el->get_right() != NULL) {
                if(father->get_value() < value) {
                    father->set_right(el->get_right());
                }
                else {
                    father->set_left(el->get_right());
                }
            }
            
            else if(el->get_left() != NULL && el->get_right() == NULL) {
                if(father->get_value() < value) {
                    father->set_right(el->get_right());
                }
                else {
                    father->set_left(el->get_right());
                }
            }
            
            return 1;
            
        }
        
        else{
            if(el->get_value() < value) {
                return rm_node(value, el->get_right(), el);
            }
            else {
                return rm_node(value, el->get_left(), el);
            }
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
    
    int rm_node(int value) {
        this->rm_node(value, this->root, NULL);
    }
};


int main() {
    
    int arr[SIZE];
    
    tree *a = new tree(), *c = new tree();
    node *b;
    
    for(int i = 0; i < SIZE; i++) {
        scanf(" %d", arr + i);
        a->add(arr[i]);
        // c->add(arr[i]);
    }
    
    // Test of order print
    a->print_order();
    a->print_pre_order();
    a->print_pos_order();
    
    // Test of element find
    b = a->find(56);
    printf("found %d at %ld\n", b->get_value(), (long) b);
    
    c->add(10);
    c->add(12);
    
    c->print_order();
    c->rm_node(12);
    c->print_order();
    
    
    return 0;
}