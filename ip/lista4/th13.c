#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
	
	char* doc = malloc(sizeof(char)*75);
	char str_buff[75];
	int doc_size = 0, nsize = 0, i;

	// while(scanf(" %75[^\n]", str_buff), strcmp("the end!", str_buff) != 0 && strcmp("THE END!", str_buff) != 0 ){
	while(fgets(str_buff, 75, stdin), strcmp("the end!", str_buff) != 0 && strcmp("the end!\nsize", str_buff) != 0 ){
		nsize = strlen(str_buff);
		doc = (char*) realloc(doc, sizeof(char)*(doc_size + nsize + 1)); //tamanho da string lida com o tamanho do \n
		//copia a string
		for (i = 0; i < nsize ; ++i) {
			if(str_buff[i] <= 'z' && str_buff[i] >= 'a') {
				doc[doc_size+i] = str_buff[i] + ('A' - 'a');
			}
			else {
				doc[doc_size+i] = str_buff[i];
			}
		}
		//adiciona o \n que foi removido.
		doc_size += nsize;
		// doc[doc_size] = '\n';
		// doc_size++;
	}

	printf("%s\n", doc);

	free(doc);

	return 0;
}