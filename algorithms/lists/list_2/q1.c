// C program to insert a node in AVL tree
#include<stdio.h>
#include<stdlib.h>
 
// An AVL tree node
struct Node
{
    int key;
    int pos;
    struct Node *left;
    struct Node *right;
    int height;
};
 
// A utility function to get maximum of two integers
int max(int a, int b);
 
// A utility function to get height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    node->pos = 0;
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update pos
    //y->pos += x->pos;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update pos
    //x->pos -= y->pos;
    
    
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert key in subtree rooted
// with node and returns new root of subtree.
struct Node* insert(struct Node* node, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key) { // left
        node->pos++;
        node->left  = insert(node->left, key);
    }
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key){
        // Update pos
        node->pos -= node->left->pos + 1;
        return rightRotate(node);
    }
 
    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        //update pos
        node->right->pos += node->pos + 1; 
        
        return leftRotate(node);
    }
 
    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        int a_pos = node->pos, b_pos = node->left->pos, c_pos = node->left->right->pos;
        
        node->pos -= b_pos + c_pos + 2;
        node->left->right->pos += b_pos + 1;
        
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        int a_pos = node->pos, b_pos = node->right->pos, c_pos = node->right->left->pos;
        
        node->right->pos -= c_pos + 1;
        node->right->left->pos += a_pos + 1;
        
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}


void get_node(struct Node* node, int key) {
	int total = 0;
	
	if(node == NULL) {
		printf("Data tidak ada\n");
		return;
	}
	
	total = node->pos + 1;
	
	while(1) {
		if(node == NULL) {
			printf("Data tidak ada\n");
			return;
		}
		
		else if(node->key < key) { // right
			total += 1;
			node = node->right;
			
			if(node != NULL) {
				total += node->pos;
			}
		}
		
		else if(node->key > key) { // left
			total -= node->pos;
			node = node->left;
			
			if(node != NULL) {
				total += node->pos;
			}
		}
		
		else { // (node->key == key) { 
			// total += node->pos;
			printf("%d\n", total);
			return;
		}
	}
}
 
void print_preorder(struct Node* root){
  if(root == NULL) {
    return;
  }
  
  printf(" %d (%d)", root->key, root->pos);
  print_preorder(root->left);
  print_preorder(root->right);
} 
 
/* Drier program to test above function*/
int main()
{
  struct Node *root = NULL;
    
  int sz = 1000000000, i, action, value;
//   scanf(" %d", &sz);
  
  for(i = 0; i < sz; i++) {
    root = insert(root, value);
  }
  
  return 0;
}