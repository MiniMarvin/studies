// construir uma HEAP
// a heap aqui construida tem index inicial 1
// número de nós internos: n/2
// número de folhas: (n+1)/2
#include <bits/stdc++.h>
#define MAX_SIZE 10000

using namespace std;

void swap(int &a, int &b){
	int t = a;
	a = b;
	b = t;
}

void printarr(int *arr, int size) {
	for (int i = 1; i <= size; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void heapify(int* heap, int node, int size) {
	int maior, buff, ct = 0;
	for(node; node <= size/2;) { // heapfy untill last left element
		// cout << node << endl;
		// verifica se tem dois filhos
		if(node < (size + 1)/2) { // a verificação ocorre no último filho / primeria folha
			// coleta o maior dos filhos
			if(heap[node*2 + 1] < heap[node*2]) {
				maior = node*2;
			}
			else {
				maior = node*2+1;
			}	
		}
		else { // um único filho
			maior = node*2;
		}

		if(heap[maior] > heap[node]) {
			swap(heap[maior], heap[node]);
			node = maior;
		}
		else{
			break;
		}
	}
}

void build_heap(int *heap, int size) {
	for (int i = size/2; i > 0; i--) {
		heapify(heap, i, size);
	}
}

// inserções ocorrem na folha
// returns new size
void insert(int *heap, int key, int size) {
	size++;
	heap[size] = key;

	for (int i = size/2; i > 0; ++i) {
		heapify(heap, i, size);
		i /= 2;	
	}
}

// occurs in the first element throwing it to the end of the array
void remove(int *heap, int size) {
	swap(heap[1], heap[size]);
	size--;
	heapify(heap, 1, size);
}

void heap_sort(int *heap, int size) {
	build_heap(heap, size);

	for (; size > 0; size--) {
		remove(heap, size);
	}	
}

int main() {
	int* heap = new int[MAX_SIZE];
	int heap_size = 10;

	for (int i = 1; i <= heap_size; ++i) {
		cin >> heap[i];
		cout << heap[i] << " ";
	}
	cout << endl;

	heap_sort(heap, heap_size);
	printarr(heap, heap_size);

}