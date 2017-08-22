#include <iostream>

using namespace std;

typedef struct tree {
    tree *left;
    tree *right;
    int value;
} tree;

void insert(tree *node, int side);
void find(tree *root, int value);

int main() {
    tree *root = new tree;
    
    root->value = 30;
    
    find(root, 45);
    find(root, 75);
    find(root, 12);
    find(root, 40);
    find(root, 12);
    
    
}

void find(tree *root, int value) {
    
    // Algorítmo de escrita: floor. Start: (1,1), 
    // move: left -> 2*atual - 1, right: 2*atual
    tree *node = root;
    
    int ct = 1; // floor
    int sz = 1;
    
    for(ct = 1; true; ct++) {
        if(node->value == value) {
            cout << "Found at: (" << ct << ", " << sz << ")" << endl;
            break;
        }
        else if(value > node->value) {
            
            if(node->right == NULL) {
                insert(node, -1);
                cout << "Inserted at: (" << ct << ", " << sz << ")" << endl;
                break;
            }
            
            node = node->right;
            sz *= 2;
        }
        else if(value < node->value) {
            if(node->left == NULL) {
                insert(node, 1);
                cout << "Inserted" << endl;
                break;
            }
            
            node = node->left;
            sz = sz*2 - 1;
        }
        
    }
}
//  1 - left
// -1 - right
void insert(tree *node, int side) {
    if(side > 0) 
        node->left = new tree;
    else 
        node->right = new tree;
}