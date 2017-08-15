#include <iostream>

#define NUM_LIMIT 100000

using namespace std;

unsigned long int fib(unsigned int x, unsigned long int* fib_arr);

// TODO: ordenar o array

int main() {

	unsigned long int fib_a;
	unsigned long int fib_arr[100000] = {0};
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
			cout << fib(j, fib_arr);
			cout << " ";
		}
		cout << endl;
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

