#include <bits/stdc++.h>

using namespace std; 

// protypes
int is_valid(char arr[][20], char visited[][20], int posx, int posy, int m, int n);

void printarr(char arr[20][20], int m, int n) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char const *argv[]) {
	
	char maze[20][20], visited[20][20];
	int tests = 0, m, n, valid, go_on = 0, bx = 0, by = 0, sz, jpnxt = 0;
	string line;


	cin >> tests;

	for (int i = 0; i < tests; ++i) {
		cin >> m;
		cin >> n;
		go_on = 0;
		sz = 0;
		getline(cin, line);

		// preenche o labirinto
		for (int j = 0; j < m; ++j) {
			getline(cin, line);
			
			for (int k = 0; k < line.length(); ++k) {
				
				maze[j][k] = line[k];
				if(maze[j][k] != '.' && maze[j][k] != '#') {
					// maze[j][k] = '.';
					// cout << "invalid" << endl;
					jpnxt = 1;
					break;
				}

			}

			if(line.length() < n) {
				for (int k = line.length(); k < n; ++k) {
					// maze[j][k] = '.';
					// visited[j][k] = 0;
					jpnxt = 1;
					break;
				}
			}

			if(jpnxt) {
				// cout << "invalid" << endl;
				// jpnxt = 0;
				break;
			}

			
		}

		if(jpnxt) {
			cout << "invalid" << endl;
			jpnxt = 0;
			continue;
		}

		for (int j = 0; j < m; ++j) {
			for (int k = 0; k < n; ++k) {
				visited[j][k] = 0;
			}
		}

		// printarr(maze, m, n);
		// cout << endl;

		// realiza a busca
		valid = is_valid(maze, visited, bx, by, m, n);
		// cout << valid << endl;
		if(valid == 1) {
			cout << "valid" << endl;
		}
		else {
			cout << "invalid" << endl;
		}
		
		
	}

	return 0;
}


pair<int, int> can_go(char arr[][20], int posx, int posy, int m, int n) {

	pair<int, int> go_on(-1,-1);
	char vd[m][n] = {0};
	int ct = 0;


	for (int i = 0; i < m; ++i) {
		if(vd[i][0] == 1) continue;

		if(arr[i][0] == '.') {
			go_on.first = i;
			go_on.second = 0;
			ct++;
		}

		vd[i][0] = 1;
	}

	for (int i = 0; i < n; ++i) {
		if(vd[0][i] == 1) continue;

		if(arr[0][i] == '.') {
			go_on.first = 0;
			go_on.second = i;
			ct++;
		}

		vd[0][i] = 1;
	}

	for (int i = 0; i < m; ++i) {
		if(vd[i][n-1] == 1) continue;

		if(arr[i][n-1] == '.') {
			go_on.first = i;
			go_on.second = n-1;
			ct++;
		}

		vd[i][n-1] = 1;
	}

	for (int i = 0; i < n; ++i) {
		if(vd[m-1][i] == 1) continue;

		if(arr[m-1][i] == '.') {
			go_on.first = m-1;
			go_on.second = i;
			ct++;
		}

		vd[m-1][i] = 1;
	}

	// cout << go_on.first << " | " << go_on.second << endl;

	if(ct != 2) {
		go_on.first = -1;
		go_on.second = -1;
	}

	return go_on;
}

// return -1 every time a path isn't possible
// return 0 every time the path doesn't matters
// return 1 every time the path is possible
int search_path(char arr[][20], char visited[][20], int posx, int posy, int m, int n) {

	// out of range
	if(posx >= m || posy >= n || posx < 0 || posy < 0) {
		return -1; 
	}

	// cout << arr[posx][posy] << "(" << '0' + visited[posx][posy] << ")";

	if(visited[posx][posy] == 1) {
		return 0;
	}

	visited[posx][posy] = 1;

	if(arr[posx][posy] == '#'){
		return -1;
	}

	if(posx == m - 1 || posy == n - 1 || posx == 0 || posy == 0) {
		if(arr[posx][posy] == '.') {
			return 1;
		}
	}

	int u[4] = {0}, max = -2;

	u[0] = search_path(arr, visited, posx, posy-1, m, n);
	u[1] = search_path(arr, visited, posx-1, posy, m, n);
	u[2] = search_path(arr, visited, posx+1, posy, m, n);
	u[3] = search_path(arr, visited, posx, posy+1, m, n);
	
	for (int i = 0; i < 4; ++i) {
		if(u[i] > max) max = u[i];
		// cout << u[i] << " | ";
	}
	// cout << endl;

	// cout << "/" << max << endl;

	return max;
}

// uma DFS para encontrar um caminho válido
int is_valid(char arr[][20], char visited[][20], int posx, int posy, int m, int n) {

	int x, y;
	pair<int, int> a = can_go(arr, posx, posy, m, n);
	x = a.first;
	y = a.second;
	visited[x][y] = 1; // garantee that the first node have been visited already

	// cout << "vals: " << m << " | " << n << endl;
	// cout << "begins: " << x << " | " << y << endl;

	int u[4] = {0}, max = -2;

	u[0] = search_path(arr, visited, x, y-1, m, n);
	u[1] = search_path(arr, visited, x-1, y, m, n);
	u[2] = search_path(arr, visited, x+1, y, m, n);
	u[3] = search_path(arr, visited, x, y+1, m, n);

	for (int i = 0; i < 4; ++i) {
		if(u[i] > max) max = u[i];
	}
	// cout << endl;

	return max;
}

