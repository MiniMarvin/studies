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

	if(size <= 8){
		if( checkPalindrome(str, 0, size-1) ) cout << 1 << endl;
		else{
			for (int i = 0; i < 8; ++i) {
				if(checkPalindrome(str, 0, i) && checkPalindrome(str, i, size-1)) {
					cout << 2;
					break;
				}
			}

			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 7; ++j) {
					if( checkPalindrome(str, 0, i) 
						&& checkPalindrome(str, i, j)
						&& checkPalindrome(str, j, size-1) ) {
						cout << 3 << endl;
						break;
					}
				}
			}

			for (int i = 0; i < 8; ++i) {
				for (int j = i + 1; j < 7; ++j) {
					for (int k = j+1; k < 6; ++k) {
						if( checkPalindrome(str, 0, i) 
							&& checkPalindrome(str, i, j)
							&& checkPalindrome(str, j, k) 
							&& checkPalindrome(str, k, size-1) ) {
							cout << 4 << endl;
							break;
						}
					}
				}
			}

			for (int i = 0; i < 8; ++i) {
				for (int j = i + 1; j < 7; ++j) {
					for (int k = j+1; k < 6; ++k) {
						for (int l = k+1; l < 5; ++l) {
							if( checkPalindrome(str, 0, i) 
								&& checkPalindrome(str, i, j)
								&& checkPalindrome(str, j, k) 
								&& checkPalindrome(str, k, size-1)
								&& checkPalindrome(str, k, size-1) ) {
								cout << 5 << endl;
								break;
							}
						}
					}
				}
			}
		}
		
	}
	


	return 0;
}

//check if something is palindrome
int checkPalindrome(char* arr, int begin, int end) {
	int check = 1;

	for (int i = 0; i <= (begin - end + 1)/2 + 1; ++i) {
		cout << arr[begin + i] << " | " << arr[end-i] << endl;
		if(arr[begin + i] != arr[end-i]) {
			check = 0;
			break;
		}
	}

	return check;
}