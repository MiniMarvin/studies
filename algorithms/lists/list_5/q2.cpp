#include <bits/stdc++.h>

#define endl '\n'
#define lli long long int
#define MAX_SIZE 200000
#define edge_t pair< int, pair< int, int > >
#define pq priority_queue< edge_t, vector<edge_t>, greater<edge_t> >

using namespace std;

bool sort_edges(edge_t a, edge_t b) {
	return  (a.first < b.first);
}

bool DFS(vector<int> g[], bool visits[], int a, int b) {
	// cout << a << " " << b << endl;

	if(visits[a]) { // já visitou, sem caminhos possíveis
		return 0;
	}

	if(a == b) {
		return 1; // entrou no vertice buscado
	}

	bool sol = 0;


	for (int i = 0; i < g[a].size(); ++i) {
		visits[a] = 1;
		sol = DFS(g, visits, g[a][i], b);
		
		if(sol) {
			// return 1;
			break;
		}
	}

	visits[a] = 0; // o vértice não tem mais nada a oferecer, desvisita

	return sol;
}

lli minimum_tree(pq &edges) {
	int visited[MAX_SIZE] = {0};
	lli min = 0;
	vector<int> g[MAX_SIZE]; // grafo da minimum spanning tree
	bool visits[MAX_SIZE] = {0}; // grafo da minimum spanning tree

	// for (int i = 0; i < edges.size(); ++i) {
	while (!edges.empty()) {
		// TODO: verificar se existe um ciclo ou não
		if(visited[edges.top().second.first] && visited[edges.top().second.second]) {
			// busca um caminho
			if(DFS(g, visits, edges.top().second.first, edges.top().second.second)) {
				edges.pop();
				continue;
			}
			// cout << "---------" << endl;
		}

		min += edges.top().first;
		visited[edges.top().second.first] = visited[edges.top().second.second] = 1;
		g[edges.top().second.first].push_back(edges.top().second.second);
		g[edges.top().second.second].push_back(edges.top().second.first);

		edges.pop();
	}

	return min;
}

int main(int argc, char const *argv[]) {
	ios::sync_with_stdio(0);
	
	lli total = 0;
	lli sum = 0;
	int m, n;
	int x, y, z;
	lli min = 0;
	
	// vector < edge_t > edges;
	pq edges;
	// priority_queue<edge_t, vector<edge_t>, greater> edges;

	while(cin >> m >> n, n != 0 || m != 0) {
		total = sum = min = 0;
		// edges.clear();

	    for (int i = 0; i < n; ++i) {
	    	cin >> x >> y >> z;

	    	total += z;
	    	// edges.push_back(make_pair(z, make_pair(x, y)));
	    	edges.push(make_pair(z, make_pair(x, y)));
	    }

	    // sort(edges.begin(), edges.end(), sort_edges);

	    // printv(edges);
	    // cout << total << endl;
	    min = minimum_tree(edges);
	    // cout << min << endl;
	    // cout << total - min << endl;
	    printf("%d\n", total - min);
	}

	return 0;
}