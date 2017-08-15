#include <iostream>

using namespace std;

long int fib(unsigned int x, long int* fib_arr);

int main() {

	long int fib_a;
	long int fib_arr[100000] = {0};
	
	
	fib_arr[0] = 0;
	fib_arr[1] = 1;

	long int u = fib(7, fib_arr);

	cout << u << endl;
	

	return 0;
}



long int fib(unsigned int x, long int* fib_arr) {
	int u = x-1;
	

	if(x-1 > 1) {	
		// caso ainda não tenha sido computado, computar
		if(fib_arr[x-1] == 0) {
			
			// Variação para computar 
			
			while(fib_arr[u] == 0) {
				u--;
			} // Encontra o último elemento computado		

			for(int i = u; i < x - 1; i++) { // Parte do último computado até o que se deseja computar
				fib_arr[i+1] = fib_arr[i] + fib_arr[i-1];
			}
		}

	}

	return fib_arr[x-1];
}

