#include <bits/stdc++.h>

using namespace std;

int checkPalindrome(char* arr, int begin, int end);

int main(int argc, char const *argv[]){
	int size, *pivotes, *pvpt, ct = 0, value = 0;
	char* str;

	scanf(" %d", &size);

	//alloc memory for str.
	str = new char[size];
	scanf("%s", str);

	pivotes = new int[size-1];

	for (int i = 0; i < size; ++i) {
		pvpt = new int[i+2];
		pvpt[0] = 0;
		pvpt[i+1] = size-1;
		for (int j = 0; j < size; ++j) {
			if((i+1)/2 != 0)pvpt[(i+1)/2] = j;
			for (int k = 0; k < i+2; ++k) {
				value += checkPalindrome(str, pvpt[k], pvpt[k+1]);
				if(value == i) {
					cout << value << endl;
					return 0;
				}
			}
		}
	}

	// int a = checkPalindrome(str, 0, size-1);
	// cout << a << endl;


	return 0;
}

//check if something is palindrome
int checkPalindrome(char* arr, int begin, int end) {
	int check = 1;
	if(begin == end)
		return 1;

	for (int i = 0; i <= (begin - end + 1)/2 + 1; ++i) {
		cout << arr[begin + i] << " | " << arr[end-i] << endl;
		if(arr[begin + i] != arr[end-i]) {
			check = 0;
			break;
		}
	}

	return check;
}