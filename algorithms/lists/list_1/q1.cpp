#include <iostream>

using namespace std;

typedef struct queue {
    queue *next = NULL;
    int value;
} queue;

void add(queue *list, int value);
void del(queue *list, int value);
queue dequeue(queue *list);

int main() {
    
    int querys = 0, action, value;
    queue *list = new queue;
    
    cin >> querys;
    
    for (int i = 0; i < querys; i++) {
        cout << "Exection " << i;
        cin >> action;
        cout << " Action: " << action << endl;
        if(action == 1) {
            cin >> value;
            add(list, value);
        }
        else if(action == 2) {
            //cin >> value;
            //del(list, value);
            *list = dequeue(list);
        }
        else if(action == 3) {
            value = list->value;
            //cout << "Plot: " << value << endl;
        }
        
        
    }
    
    return 0;
}
/*
queue del_recursive (queue *element, int value) {
    if(element->next == NULL){
        delete element;
        return NULL;
    }
    
    else if(value == element->value) {
        queue *clone = element->next;
        delete element;
        return clone;
    }
    
    element->next = (queue*) del_recursive(element->next, value);
    return element;
}
*/


void del(queue *list, int value) {
    queue *clone = list;
    queue *father = list;
    
    while(clone->next != NULL) {
        
        if( clone->value == value) {
            father->next = clone->next;
            delete clone;
            break;
        }
        
        father = clone;
        clone = clone->next;
    }
    
    delete clone;
}

queue dequeue(queue *list) {
    queue *clone = list->next;
    if(list->next != NULL) {
        delete list;
        return *clone;
    }
    else {
        
    }
}

void add(queue *list, int value) {
    queue *clone = list;
    
    while(clone->next != NULL) {
        clone = clone->next;
    }
    
    clone->next = new queue;
    clone = clone->next;
    clone->value = value;
}
