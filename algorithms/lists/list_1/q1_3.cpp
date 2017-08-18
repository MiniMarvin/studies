#include <iostream>

using namespace std;

int main() {

	int *numeros = new int[1000000];

	int register in_num, action, ct = -1;

	cin >> in_num;

	for (int i = 0; i < in_num; ++i) {
		cin >> action;
		if(action == 1) {
			ct++;
			cin >> numeros[ct];
		}
		else if(action == 2) {
			// remove();
			numeros++;
			if(ct >= 0) ct--;
		}
		else {
			//printf("%d\n", numeros[0]);
			if(ct < 0) {
				cout << "Empty!" << endl;
			}
			else {
				cout << numeros[0] << endl;
			}
		}
	}


	return 0;
}
