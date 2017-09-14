// heap starting at 1
#include <bits/stdc++.h>

#define HEAP_SIZE 1000000

using namespace std;

void swap(int &a, int &b) {
    int  t = a;
    a = b;
    b = t;
}

void print_arr(int *heap, int size) {
    for(int i = 1; i <= size; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

void min_heapify(int *heap, int pos, int size) {
    int menor = 0;
    
    // verify if only one son
    for(pos; pos <= size/2;) {
        // get the bigger
        if(pos < size/2){
            if(heap[pos*2] < heap[pos*2 + 1]){
                menor = pos*2;
            }
            else {
                menor = pos*2 + 1;
            }
        }
        else {
            menor = pos*2; // only left son
        }
        
        if(heap[pos] > heap[menor]){
            swap(heap[menor], heap[pos]);
            pos = menor;
        }
        else {
            pos = size;
        }
    }
}

void max_heapify(int *heap, int pos, int size) {
    int maior = 0;
    
    // verify if only one son
    for(pos; pos <= size/2;) {
        // get the bigger
        if(pos < size/2){
            if(heap[pos*2] > heap[pos*2 + 1]){
                maior = pos*2;
            }
            else {
                maior = pos*2 + 1;
            }
        }
        else {
            maior = pos*2; // only left son
        }
        
        if(heap[pos] < heap[maior]){
            swap(heap[maior], heap[pos]);
            pos = maior;
        }
        else {
            pos = size;
        }
    }
}

void build_max_heap(int *heap, int size) {
    // start by the last node that isn't a leaf
    for(int i = size/2; i > 0; i--) {
        max_heapify(heap, i, size);
    }
}

void build_min_heap(int *heap, int size) {
    // start by the last node that isn't a leaf
    for(int i = size/2; i > 0; i--) {
        min_heapify(heap, i, size);
    }
}

int get_cost(int *heap, int size) {
    int cost = 0;
    int pos = 1;
    int menor;
    int sum = 0;
    int old_sum = 0;
    int i = size;
    
    build_min_heap(heap, size);
    
    sum = heap[1];
    
    swap(heap[1], heap[i]);
    i--;
    min_heapify(heap, 1, i);
    
    for(; i > 0;) {
        
        sum += heap[1];
        swap(heap[1], heap[i]);
        i--;
        min_heapify(heap, 1, i);
        
        cout << cost << "/" << sum << " ";
        cost += sum;
    }
    
    return cost;
}

// build minheap and pop it out
int main() {
    int *heap = new int[HEAP_SIZE];
    int sz = HEAP_SIZE;
    int peso = 0;
    int in_size = 0;
    int menor = 0;
    
    while(1) {
        cin >> in_size;
        
        if(in_size == 0) {
            break;
        }
        
        // insert into a new heap
        for(int i = 1; i <= in_size; i++) {
            cin >> heap[i];
        }
        
        cout << endl;
        print_arr(heap, in_size);
        
        peso = get_cost(heap, in_size);
        cout << peso << endl;
    }
    
    
    return 0;
}