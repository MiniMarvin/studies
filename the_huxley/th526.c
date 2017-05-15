#include <stdio.h>
#include <stdlib.h>

// #define menor(x, y) (x < y)? x : y
// #define maior(x, y) (x > y)? x : y

int menor(int x, int y) {
	if( x < y) return x;
	return y;
}

int maior(int x, int y) {
	if( x > y) return x;
	return y;
}

int main(int argc, char const *argv[]) {
	
	int s1 = 0, s2 = 0, overflow = 0, buff = 0, i, sz1, sz2;
	char n1[10000];
	char n2[10000];
	char sum[10001];
	char sum_i[10001];

	scanf(" %s", n1);
	scanf(" %s", n2);

	for (s1 = 0; n1[s1] != '\0'; ++s1);
	for (s2 = 0; n2[s2] != '\0'; ++s2);

	// while(scanf("%c", &n1[s1]), n1[s1] >= '0' && n1[s1++] <= '9');
	// while(scanf("%c", &n2[s2]), n2[s2] >= '0' && n2[s2++] <= '9');

	sz1 = menor(s1, s2);
	sz2 = maior(s1, s2);

	//faz a soma caractere a caractere.
	//TODO: fazer o deslocamento da menor string, pois, do contrário vai somar a ponta com lixo de memória.
	for (i = sz2 - 1; i >= 0; --i) {
		//TODO: rever como está ocorrendo a aritmética de posições, pois está inconsistente.
		if(s1 > s2) {
			if( (i - s2 + 1) < 0 ) {
				buff = n1[i] + overflow - '0';
				overflow = 0;
				printf("n1: %c\n", n1[i]);
			}

			else {
				buff = n1[i] + n2[(i - s2 + 1)] - '0' - '0';
				printf("n1: %c | n2: %c | %d\n", n1[i], n2[(i - s2 + 1)], (i - s2 + 1));
			}
			printf("buff: %d\n", buff);
		}

		else if( s1 < s2) {
			if( i + s2 - s1 - 1 < 0 ) {
				buff = n1[i] + overflow - '0';
				overflow = 0;
			}

			else {
				buff = n1[i + s2 - s1 - 1] + n2[i] - '0' - '0';
			}
		}

		else {
			buff = n1[i] + n2[i] - '0' - '0'; //soma o fim da maior string com o fim da menor.
			// printf("buff5: %d\n", buff);
		}
		
		// buff = s1[i] + s2[i] - '0' - '0';
		sum_i[sz2-i] = overflow + buff%10 + '0';
		overflow = (overflow + buff)/10;
	}

	//adiciona uma casa caso tenha ultrapassado o limite
	if(overflow > 0) {
		sz2 += 1;
		i = sz2;
		sum_i[i] = overflow + '0';
	}
	
	//inverte a string sum.
	for (i = sz2; i >= 0; --i) {
		sum[sz2 - i] = sum_i[i];
		printf("%c", sum[sz2 - i]);
	}

	printf("\n");

	

	return 0;
}

