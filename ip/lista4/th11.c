// Recebe as strings
// compara as trings
// realoca os espaços
// substitui as subs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareStr(char* str1, char* str2, int begin, int sz);

int main(int argc, char const *argv[]) {
	
	int m, n, i, tlen;
	char text[1000];
	char correct[1000];
	char[100][200] dicio_words;
	char[100][200] dicio_originals;
	
	while(scanf(" %d %d", &m, &n), m != 0 && n != 0) {
		
		// Read all the words in dicio (the dicio is just one for every input)
		for (i = 0; i < m; ++i) {
			scanf(" %s -> %s", dicio_originals, dicio_words[i]);
		}

		// Le todas as linhas
		for (i = 0; i < n; ++i) {
			scanf(" %1000[^\n]", text);
			tlen = strlen(text);

			// Formata a linha lida
			for (i = 0; i < strlen; ++i) {
				
			}
		}
	}

	scanf(" %[^\n]", str1);

	

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