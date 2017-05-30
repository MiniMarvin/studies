#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	
	char str[200];

	scanf("%s", str);

	formatInput(str);

	return 0;
}


void formatInput(char *str) {
	int sz, i, ct, begin, state;

	sz = strSize(str);

	for (i = 0; i < sz; ++i) {
		//encontrou uma sequência de espaços.
		if(str[i] == ' ') {
			if(ct == 0) {
				begin = i;
			}
			ct++;
		}
		
		//saiu da sequência
		else {
			if(ct > 0) {
				//reposiciona os caracteres da string até o '\0'
				for (j = begin + 1; j <= sz - ct + 1; ++j) {
					
				}
			}
		}
	}
}

int strSize(char *str) {
	int i;
	for (i = 0; str[i] != '\0'; ++i);
	return i;
}