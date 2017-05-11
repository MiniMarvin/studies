#include <stdio.h>

int main() {
	// char* number;
	int num, maior = 0, menor = 10000, buff, i, arr[200] = {0}, lastbit = 0;
	scanf(" %d", &num);

	// number = (char*) malloc(sizeof(char)*num);

	//make a flag system to don't have to order the array
	for (i = 0; i < num; ++i) {
		scanf(" %d", &buff);
		arr[buff] = 1;
		if(buff < menor) menor = buff;
		if(buff > maior) maior = buff;
	}

	buff = (menor+maior)/2;
	lastbit = (menor+maior)&1;
	i = 0;

	while(1) {
		if(arr[buff + i + lastbit] == 1) {
			buff += i + lastbit;	
			break;
		}
		if(arr[buff-i] == 1){
			buff -= i;
		}
		i++;
	}
	
	printf("%d %d %d\n", menor, buff, maior);

	return 0;
}