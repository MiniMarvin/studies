// TODO: para cada nova árvore adicionar o diretório pai

#include <bits/stdc++.h>

using namespace std;

// class prototypes
class node;
class bst;

// class definitions
class node{
public:
    string name;
    node *left;
    node *right;
    node *father;
    bst *dir;
    int isdir;
    
    node(string name, int isdir) {
        this->name = name;
        this->isdir = isdir;
        this->left = NULL;
        this->right = NULL;
        this->father = NULL;
        this->dir = NULL;
    }
};

class bst{
private:
    bst* father;

    // Insert a file in the folder
    node *insert(string name, node* el, int isdir) {
        if(el == NULL) {
            return new node(name, isdir);
        }
        
        // Verifica se o elemento já existe
        if((el->name).compare(name) == 0) {
            cout << "File exists" << endl;
            return el;
        }
        
        // Se não verifica se o elemento adicionado é menorr que o atual
        if(this->vale_menos(name, el->name) == 1) {
            el->left = insert(name, el->left, isdir);
            
            // Verifica se é diretório e se for gera uma nova árvore
            if(isdir == 1) {
                el->left->dir = new bst();
            }
            else {
                el->left->dir = NULL;
            }
        }
        else {
            el->right = insert(name, el->right, isdir);
            
            // Verifica se é diretório e se for gera uma nova árvore
            if(isdir == 1) {
                el->right->dir = new bst();
            }
            else {
                el->right->dir = NULL;
            }
        }
        
        return el;
    }
    
    void print_pre_order(node *el) {
        if(el == NULL) return;
        
        cout << el->name << " ";
        print_pre_order(el->left);
        print_pre_order(el->right);
    }
    
    void print_pre_order_dirs(node *el) {
        if(el == NULL) return;
        
        if(el->isdir == 1){
            cout << el->name << " ";
        }
        print_pre_order_dirs(el->left);
        print_pre_order_dirs(el->right);
    }
    
    // finds a dir inside actual dir
    node *find(string name, node *el) {
        if(el == NULL) {
            return NULL;
        }
        if(el->name == name) {
            return el;
        }
        if(this->vale_menos(name, el->name) == 1) {
            return this->find(name, el->left);
        }
        return this->find(name, el->right);
    }
    
    
public:
    node* root;

    bst(){
        this->root = NULL;
    }
    
    node *insert(string name, int isdir) {
        // cout << "adding " << name << endl;
        this->root = this->insert(name, this->root, isdir);
    }
    
    // print 1 if a < b, and 0 otherwise
    int vale_menos(string a, string b) {
        string min = a;
        int menor = a.length();
        int status = 0;
        
        if(b.length() < menor) {
            menor = b.length();
            min = b;
            status = 1;
        }
        
        for(int i = 0; i < menor; i++) {
            if(b[i] == a[i]) {
                continue;
            }
            if(b[i] > a[i]) {
                // return a;
                return 0;
            }
            // return b;
            return 1;
        }
        
        // return min;
        return status;
    }
    
    // print every file in actual dir in preorder
    void print_pre_order() {
        print_pre_order(this->root);
        cout << endl;
    }
    
    // print every dir in preorder
    void print_pre_order_dirs() {
        print_pre_order_dirs(this->root);
        cout << endl;
    }
    
    // finds a dir inside actual dir
    node *find(string name) {
        return this->find(name, this->root);
    }
    
    /**
     * Returns the folder pointer of the new directory
     **/
    bst* cd(string name) {
        node *a = find(name);
        if(a == NULL) {
            cout << "not found" << endl;
            return NULL;
        }
        bst *folder = a->dir;
        return folder;
    }
    
};


int vale_menos(string a, string b) {
    string min = a;
    int menor = a.length();
    int status = 0;
    
    if(b.length() < menor) {
        menor = b.length();
        min = b;
        status = 1;
    }
    
    for(int i = 0; i < menor; i++) {
        if(b[i] == a[i]) {
            continue;
        }
        if(b[i] > a[i]) {
            // return a;
            return 0;
        }
        // return b;
        return 1;
    }
    
    // return min;
    return status;
}

int main() {
    
    bst *a = new bst();
    
    a->insert("/", 1);
    a->insert("bin", 1);
    a->insert("dev", 1);
    a->insert("home", 1);
    a->insert("home", 1);
    a->insert("cache", 0);
    a->insert("nil", 0);
    
    a->print_pre_order();
    a->print_pre_order_dirs();
    
    
    return 0;
}


void testa_menor() {
    string arr[2];
    string a("BB");
    string b("BBBB");
    arr[0] = a;
    arr[1] = b;
    
    cout << arr[vale_menos(a, b)] << endl;
}