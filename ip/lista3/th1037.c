/**
 * Projeto: Realizar o cálculo de um sistema linear por diversos métodos
 * Entrada: número de variáveis, número máximo de iterações, erro
 * 	
 * References:
 * 	- http://stackoverflow.com/questions/3414827/how-to-pass-a-2d-dynamically-allocated-array-to-a-function
 */

#include <stdio.h>
#include <stdlib.h>

#define abs(x) (x < 0) ? -x : x

//function prototypes
void unpivotGauss(double** a, double b[], double* x, int n);
void pivotGauss(double** a, double b[], double x[], int n);
void swap_lines(double** a, double b[], int addr, int x);

int main(int argc, char const *argv[]) {

	int size, i, j, k = 0;
	int col, row;
	double ** coefs;
	
	while(scanf(" %d", &size) != EOF) {
		/************************************************************************************************
		 * Declarando o array de forma dinâmica para utilizar com mais facilidade nas funções.			*
		 ************************************************************************************************/
		// printf("size: %d\n", size);
		col = size+1, row = size;

		coefs = (double**)malloc(sizeof(double*)*size);
		for(i = 0 ; i < col;i++){
		    *(coefs+i) = (double*)malloc(sizeof(double)*size);
		}

		double consts[size], b[size];
		/************************************************************************************************/

		for (i = 0; i < size; ++i) {
			for (j = 0; j < size; ++j) {
				// printf("%d | %d\n", i, j);
				scanf(" %lf", &coefs[i][j]);
			}
			scanf(" %lf", &consts[i]);
		}

		printf("Case #%d: ", ++k);
		pivotGauss(coefs, consts, b, size);
		for (i = 0; i < size - 1; ++i) {
			printf("%.2lf ", b[i]);
		}
		printf("%.2lf\n", b[size-1]);
	}
	



	return 0;
}

/**
 * @brief      Calcula a resolução do sistema linear baseado no método de escalonamento de Gauss sem Pivotação.
 *
 * @param      a	   A matriz de coeficientes que será recebida.
 * @param      b       A matriz de constantes de cada equação.
 * @param[in]  x       A matriz solução do sistema de equações após o fim do processo.
 * @param[in]  n       O número de variáveis do sistema de equações.
 */
void unpivotGauss(double** a, double b[], double x[], int n) {

	int i = 0, k, j;
	double m, s; //variáveis de buffer.

	// printf("\n\nsoluções:\n");
	
	// for (i = 0; i < n; ++i) {
	// 	for (j = 0; j < n; ++j){
	// 		printf("%lf ", a[i][j]);
	// 	}
	// 	printf("\n");
	// }

	// ELIMINAÇÃO DO SISTEMA DE EQUAÇÕES
	// realiza a operação para transformar a matriz em diagonal superior
	for (k = 0; k < n; ++k) {
		for (i = (k+1); i < n; i++) {
	        m = a[i][k]/a[k][k];
	        //a[i][k]=0;
	        for (j = k; j < n; j++) {
		        a[i][j] = a[i][j] - (m*a[k][j]);
		    }
		    b[i] = b[i] - (m*(b[k]));
		}
	}

	//RESOLUÇÃO DO SISTEMA DE EQUAÇÕES
	x[n-1] = b[n-1]/a[n-1][n-1];
	for (k = (n-2); k >= 0; k--){
		s = 0;
		//itera no array realizando sucessivas subtrações dos coeficientes.
		for (j = k;j < n; j++) {
		   s = s + ( a[k][j]*x[j] );
		}

		x[k]=(b[k] - s)/(a[k][k]);
	}
}

/**
 * @brief      Realiza as estratégias de pivoteamento antes de enviar os dados para a unpivotGauss.
 *
 * @param      a	   A matriz de coeficientes que será recebida.
 * @param      b       A matriz de constantes de cada equação.
 * @param[in]  x       A matriz solução do sistema de equações após o fim do processo.
 * @param[in]  n       O número de variáveis do sistema de equações.
 */
void pivotGauss(double** a, double b[], double x[], int n) { //escalonamento gaussiano
	
	double max = 0;
	int addr = 0, i, j, u, v;

	for (i = 0; i < n; ++i) {
		max = 0;
		for (j = i; j < n; ++j) {
			if(abs(a[j][i]) > max) {
				max = abs(a[j][i]);
				addr = j;
			}
		}
		swap_lines(a, b, addr, i);

	}

	unpivotGauss(a, b, x, n);
}

/**
 * @brief      Realiza a troca de linhas de um sistema linear
 *
 * @param      a     Matriz de coeficientes.
 * @param      b     Matriz de constantes.
 * @param[in]  addr  Número da linha que deseja trocar.
 * @param[in]  x     Número da linha que deseja trocar.
 */
void swap_lines(double** a, double b[], int addr, int x) {
	double *t = *(a+addr);
	*(a+addr) = *(a+x);
	*(a+x) = t;

	double u = b[addr];
	b[addr] = b[x];
	b[x] = u;
}