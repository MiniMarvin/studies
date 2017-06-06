#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareStr(char* str1, char* str2, int begin, int sz);

int main(int argc, char const *argv[]) {
	
	char str1[200];
	char str2[200];
	int occurrency = 0, sz1, sz2, i, diff;

	scanf(" %[^\n]", str1);
	scanf(" %[^\n]", str2);

	// Get the second string size and make an iteration throught the first one.
	sz1 = strlen(str1);
	sz2 = strlen(str2);
	diff = sz1-sz2;

	for (i = 0; i <= diff; ++i) {
		if(compareStr(str1, str2, i, sz2)) {
			occurrency++;
		}
	}
	printf("%d\n", occurrency);

	return 0;
}

/**
 * @brief      Compare if the substring is in some specific spot.
 *
 * @param      str1   The string 1
 * @param      str2   The string 2
 * @param[in]  begin  The begin of the process in string 1
 * @param[in]  sz     The size of string 2
 *
 * @return     0 - aren't equal
 * 			   1 - they're equal
 */
int compareStr(char* str1, char* str2, int begin, int sz) {
	int ret = 1, i;
	for (i = 0; i < sz; ++i) {
		if(str2[i] != str1[begin + i]) {
			ret = 0;
			break;
		}
	}
	return ret;
}