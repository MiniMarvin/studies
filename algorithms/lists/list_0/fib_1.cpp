#include <iostream> 

using namespace std;

long int fib(int pos);
long int fibArr(int begin, int end, long int *arr);
void printArr(long int *arr, int size);
void insertion_sort(long int *arr, int size, int order);


// TODO: recebe todos os valores e calcula os valores de fibonacci somente necessários para aquelas operações
int main() {
	
	int in_num = 0;
	
	cin >> in_num;
	
	// create the arrays
	long int *in_a = new long int[in_num];
	long int *in_b= new long int[in_num];
	
	cin >> in_a[0];
	cin >> in_b[0];
	
	long int lower = in_a[0];
	long int bigger = in_a[0] + in_b[0];
	
	long int max_diff = 0;
	
	
	// receive all the possible inputs
	for (int i = 1; i < in_num; i++) { // starts in 1 because the 0 has already been done
		cin >> in_a[i];
		cin >> in_b[i];
		
		// update what we need to compute in fibonacci sequence
		if(in_a[i] < lower) {
			lower = in_a[i];
		}
		
		if(in_a[i] + in_b[i] > bigger) {
			bigger = in_a[i] + in_b[i];
		}
		
		if(in_b[i] > max_diff) {
			max_diff = in_b[i];
		}
		
	} 
	
	// Create array to store all the need to compute arrays
	//long int *fib_arr = new long int[bigger - lower];
	long int *fib_arr = new long int[bigger];
	
	// Compute all of them
	fibArr(lower, bigger + 1, fib_arr);
	
	// Generate the array that will be ploted with the biggest size possible
	long int *p_arr = new long int[max_diff];
	// long int *p_arr = new long int[101];
	
	for(int i = 0; i < in_num; i++) { // clone, order and print all of them.
		// Generate the array that will be ploted now
		int sum = in_a[i] + in_b[i];
		
		p_arr[0] = fib_arr[in_a[i] - 1];
		
		// Põe eles em ordem decrescente os 100 primeiros
		for(int j = in_a[i], k = 1; k < in_b[i] + 1; j++, k++) {
			p_arr[k] = fib_arr[j];
			
			// Verifica se está nos 100 primeiros
			if(k < 100) {
				long int key = p_arr[k - 1];
				
				if(fib_arr[j] < key) {
					for(int u = k; u > 0 && fib_arr[j] < p_arr[u - 1]; u--) { // vai procurando o menor para inserir lá
						p_arr[u] = p_arr[u - 1]; // Põe para frente
						p_arr[u - 1] = fib_arr[j]; // Coloca o novo elemento no ponto correto
					}
					
					
				}
			}
			else { // se não está volta para o fim dos 100 primeiros elementos e itera lá
				int key = p_arr[99];
				
				if(fib_arr[j] < key) {
					for(int u = 99; u > 0 && fib_arr[j] < p_arr[u - 1]; u--) { // vai procurando o menor para inserir lá
						p_arr[u] = p_arr[u - 1]; // Põe para frente
						p_arr[u - 1] = fib_arr[j]; // Coloca o novo elemento no ponto correto
					}
				}
			}
		}
		
		
		cout << "Case " << i + 1 << ": ";
		// print p_arr
		printArr(p_arr, in_b[i] + 1);
	}
	
	//printArr(fib_arr, bigger - lower);
	
	
	delete[] in_a;
	delete[] in_b;
	
	return 0;
}

long int fib(int pos) {
	long int fib_val = 0;
	int old[] = {0,1};
	
	if(pos == 1) {
		fib_val = 0;
	}
	else if(pos == 2) {
		fib_val = 1;
	}
	
	else {
		
		for (int i = 1; i < pos; i++) {
			fib_val = old[0] + old[1];
			old[0] = old[1];
			old[1] = fib_val;
		}
		
	}
	
	return fib_val;
}


long int fibArr(int begin, int end, long int *arr) {
	long int fib_val = 0;
	int old[] = {0,1};
	begin = 1;
	arr[0] = 0;
	arr[1] = 1;
	
	for (int i = 3; i < end; i++) {
		
		fib_val = (old[0] + old[1])%100000;
		old[0] = old[1];
		old[1] = fib_val;
		
		if(i >= begin) { // records the necessary fibonacci values
			arr[i - begin] = fib_val;
		}
	}
	
	return fib_val;
}

void printArr(long int *arr, int size) {
	if(size > 100) size = 100;
	
	for (int i = 0; i < size ; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}