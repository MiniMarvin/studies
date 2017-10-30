#include <bits/stdc++.h>

#define endl '\n'
#define MAX_SIZE 200000

using namespace std;

class graph {
public:
	vector< pair<int, int> > e[MAX_SIZE];

	graph() {

	}
	~graph(){

	}

	void print_e() {
		for (int i = 0; i < MAX_SIZE; ++i) {
			for (int j = 0; j < e[i].size(); ++j) {
				cout << this->e[i][j].second << " (" << this->e[i][j].first << ") ";
			}
			if(e[i].size()) {
				cout << endl;
			}
			
		}
	}

	void add_e(int a, int b, int w) {
		if(!this->find_e(a, b)) {
			this->e[a].push_back(make_pair(w, b));
			this->e[b].push_back(make_pair(w, a));
		}
	}

	bool find_e(int a, int b) {
		for (int i = 0; i < e[a].size(); ++i) {
			if(e[a][i].second == b) {
				return 1;
			}
		}
		return 0;
	}

	void dijkstra(int v) {
		// create e clone with height inf and the beginning border with wight as 0

		// create a binary vector wich contains the binary representation to every single
		// line to be connect at it.

		// make an priority queue and insert the beginning vertex into it

		// process the extracted vertex and update every single adjacent border

		// insert the updated borders into the priority queue

		// goes doing it untill the priority queue is empty or the marks become all processed
	}
};


int main(int argc, char const *argv[]) {
	ios::sync_with_stdio(0);
	int m, n;
	int a, b, w;

	graph g;

	while(cin >> m >> n, m != 0 && n != 0) {
		
		for (int i = 0; i < n; ++i) {
			cin >> a >> b >> w;
			g.add_e(a, b, w);
			cout << "a: " << a << " b: " << b << " w: " << w << endl;
		}
		
	}
 
	g.print_e();


	return 0;
}