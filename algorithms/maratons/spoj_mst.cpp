#include <bits/stdc++.h>

#define inf 0x3f3f3f3f
#define MAX_SIZE 10000

using namespace std;

class graph{
public:
	vector<pair<int, int> > e[10000];

	graph() {}
	~graph(){}

	void add_e(int a, int b, int w) {
		this->e[a].push_back(make_pair(w, b));
		this->e[b].push_back(make_pair(w, a));
	}

	// obs: every negative weight will be ignored to avoid another var to markers
	void prim(int a, int n) {
		pair<int, int> v[] = new pair<int, int>[n];
		pair<int, int> mst[] = new pair<int, int>[n];
		pair<int, int> *leaf = NULL;

		int aux = 0;

		for (int i = 0; i < MAX_SIZE; ++i) {
			v[aux].first = inf;
			mst[aux].first = inf;
			for (; i < MAX_SIZE; ++i) {
				if(e[i].size() > 0) {
					v[aux].second = i;
					mst[aux].second = i;
					break; // forces the next iteration
				}
			}
			aux++;
		}

		// get the first vertex
		v[0].first = 0;

		// run the iteration for every vertex
		for (int i = 0; i < n; ++i) {
			// get the vertex
			aux = menor(v);
			leaf = &v[aux];
			// if not insert it into the MST
			for (int j = 0; j < e[(*leaf).second].size(); ++j) { // iter throught every adjacent node
				// find the respective node and gives the correct value to it
				for (int k = 0; k < n; ++k) {
					if(e[(*leaf).second][j].second == v[k].second) {
						mst[k].first = min(mst[k].first, (*leaf).first + e[(*leaf).second][j].first);
						break;
					}
				}
			}
			// mark visited
			(*leaf).first = -1;
		}

	}

	int menor(pair<int, int> &a) {
		int m = 0;

		for (int i = 0; i < a.size(); ++i) {
			if(v[i].first < v[m].first && v[i] > 0) {
				m = i;
			}
		}

		return m;
	}

	void kruskall(){

	}
}


int main() {


	
	return 0;
}