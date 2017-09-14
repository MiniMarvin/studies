// heap starting at 1
#include <bits/stdc++.h>

#define HEAP_SIZE 10

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

void heapify(int *heap, int pos, int size) {
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

void build_heap(int *heap, int size) {
    // start by the last node that isn't a leaf
    for(int i = size/2; i > 0; i--) {
        heapify(heap, i, size);
    }
}

void heap_sort(int *heap, int size) {
    
    build_heap(heap, size);
    
    for(int i = size; i > 0; i--) {
        swap(heap[i], heap[1]);
        heapify(heap, 1, i - 1);
    }
}



int main() {
    int *heap = new int[HEAP_SIZE + 1];
    int sz = HEAP_SIZE;
    
    for(int i = 1; i < HEAP_SIZE; i++) {
        cin >> heap[i];
    }
    
    heap_sort(heap, sz);
    print_arr(heap, sz);
    
    return 0;
}