// TODO: resolver o problema do insertion sort

#include <iostream>
#include <cstdio>
#include <cstdlib>

#define MAX_SIZE 100
#define MAX_NUM 100

using namespace std; 

// int randArr(int **arr);
int randArr(int *&arr);
void insertion_sort(int *arr, int size, int order);

int main(int argc, char const *argv[]) {
	
	srand(time(NULL));
	
	int* arr;
	int size = 0;
	int order = 1;
	
	if(argc > 1) {
		order = atoi(argv[1]);
		cout << "got: " << order << endl;
	}

	size = randArr(arr);
	cout << "size: " << size << endl;

	// Unity test area----------//
	FILE* fp= fopen("b2.txt", "w"); 
	for (int i = 0; i < size; ++i) {
		fprintf(fp, "%d\n", arr[i]);
	}
	fclose(fp);
	//--------------------------//

	insertion_sort(arr, size, order);

	return 0;
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

	// Unity test area----------//
	FILE* fp= fopen("b1.txt", "w+"); 
	for (int i = 0; i < size; ++i) {
		// fprintf(fp, "%d\n", (*arr)[i]);
		fprintf(fp, "%d\n", arr[i]);
	}

	fclose(fp);
	//--------------------------//

	return size;
}

/**
 * @brief      sort the array based in insertion sort algorithm
 *
 * @param      arr    The arr
 * @param[in]  size   The size of the array
 * @param[in]  order  The order positive value to ascending and negative value for descending
 */
void insertion_sort(int *arr, int size, int order) {
	
	int key = 0;

	
	for (int i = 1; i < size; ++i) {

		key = arr[i];
		int j = i - 1;

		// growing order
		for (; j > 0 && ( order > 0 ? arr[j] > key : arr[j] < key ); --j) {
			arr[j+1] = arr[j];
		}
		
		if(j >= 0 && ( order > 0 ? arr[j] > key : arr[j] < key ) )
			arr[j] = key;
		
	}

	for (int i = 0; i < size; ++i) {
		cout << arr[i] << " ";
	}

	cout << endl;

}