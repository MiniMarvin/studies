#include <iostream>
#include <cstdlib>

#define MAX_SIZE 20
#define MAX_NUM 100

using namespace std;

int randArr(int *&arr);
void insertion_sort(int *arr, int size, int order);

int main(int argc, char** argv) {

    srand(time(NULL));

    int *arr;
    int size;
    int order = 1;
    
    // if user input the order the system will use it as order
    if(argc > 1) {
        order = atoi(argv[1]);
    }
    
    size = randArr(arr);
    
    insertion_sort(arr, size, order);
    
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return EXIT_SUCCESS; 
}


/**
 * @brief      Generate a random size array with random numbers.
 *
 * @param      arr   The arr pointer where it's going to be allocated.
 *
 * @return     The array size.
 */
int randArr(int *&arr) {

	int size = rand()%MAX_SIZE;
	cout << "size: " << size << endl;

	// *arr = new int[size];
	arr = new int[size];

	for (int i = 0; i < size; ++i) {
		// (*arr)[i] = rand();
		arr[i] = rand()%MAX_NUM;
		cout << arr[i] << " ";
	}

	cout << endl;

	return size;
}


void insertion_sort(int *arr, int size, int order) {
    
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