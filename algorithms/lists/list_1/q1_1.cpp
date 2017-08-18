#include <iostream>

using namespace std;

// TODO: create container class and put the elements inside it

class queue {
    private:
        int is_void = 1;
        int value = 0;
        queue *next_element = NULL;
    public:
    
        void dequeue() {
            if(this->next_element == NULL) {
                is_void = 1;
            }
            else {
                queue *buff = this;
                this = this->next_element;
                delete buff;
            }
        }
        
        void add(int value) {
            
            queue *lista = this;
            
            if(this->is_void == 0) {
            
                while(lista->next_element != NULL) {
                    lista = lista->next_element;
                }
                
                lista->next_element = new queue();
                lista = lista->next_element;
            
            }
            
            lista->value = value;
            this->is_void = 0;
        }
        
        void printVal() {
            if(is_void == 1) {
                cout << "Empty!" << endl;
            }
            else {
                cout << this->get_val() << endl;
            }
        }
        
        void printAll() {
            if(is_void == 1) {
                cout << "Empty!" << endl;
            }
            else {
                queue *lista = this;
                while(lista != NULL) {
                    cout << lista->get_val() << endl;
                    lista = lista->next_element;
                }
            }
        }
        
        int get_val() {
            return this->value;
        }
        
        queue get_next() {
            return *(this->next_element);
        }
};

int main() {
    queue *lista = new queue();
    
    lista->add(120);
    lista->add(130);
    lista->add(140);
    lista->add(150);
    lista->add(160);
    lista->add(170);
    
    lista->printAll();
    
    cout << endl;
    
    lista->dequeue();
    lista->printAll();
    
    return 0;
}