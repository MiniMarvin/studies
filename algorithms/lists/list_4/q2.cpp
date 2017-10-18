#include <bits/stdc++.h>

using namespace std;

// prototypes
int comp_num(char arr[100][100], int m, int n);
void join(int arr[100][100], int xa, int ya, int xb, int yb, int m, int n);
int find(int arr[100][100], int x, int y, int m, int n);

void printarr(int arr[100][100], int m, int n) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char const *argv[]) {
	char arr[100][100];
	int m, n;
	string line;

	while(cin >> m, cin >> n, m != 0) {
		getline(cin, line); // remove o primeiro \n do buffer
		for (int i = 0; i < m; ++i) {
			getline(cin, line);
			for (int j = 0; j < n; ++j) {
				arr[i][j] = line[j];
				// cout << arr[i][j];
			}
			// cout << endl;
		}

		// realiza o set join
		cout << comp_num(arr, m, n) << endl;
		
	}

	return 0;
}

int cont(char arr[100][100], int joint[100][100], int m, int n){
	int ct = 0;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			// só conta os conjuntos que são de @
			if(joint[i][j] == i*n + j && arr[i][j] == '@') {
				ct++;
			}
		}
	}
	return ct;
}

void join_borders(char arr[100][100], int joint[100][100], int x, int y, int m, int n) {
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if(x + i < 0 || y + j < 0 || x + i >= m || y + j >= n) continue;
			
			if(arr[x + i][y + j] == '@') {
				join(joint, x, y, x + i, y + j, m, n);
			}
		}
	}
}

int comp_num(char arr[100][100], int m, int n) {
	int joint[100][100];
	int flag = 0;

	// gera os representates dos nós
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			joint[i][j] = n*i + j;
		}
	}
	
	// cout << "joint:" << endl;
	// printarr(joint, m, n);
	// cout << endl;

	// vai juntando os conjuntos
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if(arr[i][j] == '@') {
				join_borders(arr, joint, i, j, m, n);
			}
		}
	}
	
	// printarr(joint, m, n);
	// cout << endl;

	return cont(arr, joint, m, n);
}

void join(int arr[100][100], int xa, int ya, int xb, int yb, int m, int n) {
	if(xa >= m || xb >= m || ya >= n || yb >= n) return;
	int u = find(arr, xa, ya, m, n);
	int x = u/n, y = u%n;

	int a = find(arr, xb, yb, m, n);
	arr[x][y] = a;
}

int find(int arr[100][100], int x, int y, int m, int n) {
	if(x >= m || y >= n) return -1;

	int u = arr[x][y];
	// cout << "u: " << u << " ";
	if(u == x*n + y) {
		return u;
	}

	return find(arr, u/n, u%n, m, n);
}