#include <iostream>
#include <array>

#define NUM_LIMIT 100000 // 10^5

using namespace std;

typedef unsigned long int uli;

unsigned long int fib(unsigned int x, unsigned long int* fib_arr);
void insertion_sort(uli *arr, int size, int order);
void printArr(uli *arr, int size);

// TODO: ordenar o array

int main() {

	unsigned long int fib_a;
	unsigned long int fib_arr[11000] = {0}; // In the maximum have 10^5 + 10^6 values
	unsigned long int arr[11000] = {0}; // In the maximum have 10^5 + 10^6 values
	unsigned long int u;
	int t_cases = 0;
	int in_a, in_b, end;
	
	// Definição da base de fibonacci
	fib_arr[0] = 0;
	fib_arr[1] = 1;

	cin >> t_cases;
	
	for(int i = 1; i <= t_cases; i++) {
		
		cin >> in_a;
		cin >> in_b;
	
		end = in_a + in_b;
		cout << "Case "	<< i << ": ";
		
	
		for(int j = in_a; j <= end; j++) {
			
			arr[j - in_a] = fib(j, fib_arr);
			//cout << " ";
			
			//arr[ j - in_a] = fib_arr[j-1];
		}
		
		insertion_sort(arr, in_b + 1, -1);
		printArr(arr, in_b + 1);
		
		//delete arr;
	}
	

	return 0;
}


unsigned long int fib(unsigned int x, unsigned long int* fib_arr) {
	int u = x-1;
	

	if(x-1 > 1) {	
		// caso ainda não tenha sido computado, computar
		if(fib_arr[x-1] == 0) {
			
			// Variação para computar 
			
			while(fib_arr[u] == 0) {
				u--;
			} // Encontra o último elemento computado		

			for(int i = u; i < x - 1; i++) { // Parte do último computado até o que se deseja computar
				fib_arr[i+1] = (fib_arr[i] + fib_arr[i-1])%NUM_LIMIT;
			}
		}

	}

	return fib_arr[x-1];
}



void insertion_sort(uli *arr, int size, int order) {
    
    // increase order
    for(int i = 1; i < size; i++) {
        
        int key = arr[i]; // make the actual value as comparison key
        int j = i-1; // start analysing the value before the key one
        
        for(;j >= 0 && (order >= 0 ? arr[j] < key : arr[j] > key); j--) {
            arr[j+1] = arr[j]; // put the array elements one element to the front
            arr[j] = key; // garant that the key is going to be placed in the correct positioin
        }
    }
}

void printArr(uli *arr, int size) {
	if(size > 100) size = 100;
	
	for (int i = 0; i < size ; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}