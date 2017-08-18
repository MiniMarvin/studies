/***
 * Author: Caio M. Gomes
 * Objective: Example code in dynamic lists made on the data structure basis
 * allows, the user to insert a node and print it all.
 ***/

#include <iostream>

using namespace std;

typedef struct list {
    list* next = NULL;
    int value = 0;
} list;

void addElement(list *head);
void printList(list *head);

int main() {
    
    //list *head = (list*) malloc(sizeof(list));
    list *head = new list;
    head->value = 0;
    
    for(int i = 0; i < 100; i++) {
        addElement(head);
    }
    
    printList(head);
    cout << endl;
    
    return 0;
}


void addElement(list *head) {
    list *node = head;
    int ct = 1;
    
    while(node->next != NULL) {
        node = node->next;
        ct++;
    }
    
    // Found list last element
    //node->next = (list*) malloc(sizeof(list));
    node->next = new list;
    node = node->next;
    
    node->value = ct; // Put the number of the node in the list
    
}

void printList(list *head) {
    list *node = head;
    
    // print all the values
    while(node->next != NULL) {
        cout << node->value << " ";
        node = node->next;
    }
}