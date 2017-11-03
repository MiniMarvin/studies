#include <bits/stdc++.h>

#define endl '\n'
#define MAX_SIZE 100000
#define INF 0x3f3f3f3f

using namespace std;

class graph {
public:
	vector< pair<int, int> > e[MAX_SIZE];

	graph() {}
	~graph(){}

	void clean() {
		for (int i = 0; i < MAX_SIZE; ++i) {
			e[i].clear();
		}
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

	// bool update_w(vector< pair<int, int> > &v, int new_w, int value) {
	bool update_w(pair<int, int> *v, int new_w, int value) {
		bool ret = 0;
		// for (int i = 0; i < v.size(); ++i) {
		// 	if(v[i].second == value) {
		// 		if(new_w < v[i].first) {
		// 			v[i].first = new_w;
		// 			ret = 1;
		// 		}
		// 		break;
		// 	}
		// }
		if(new_w < v[value].first) {
			v[value].first = new_w;
			ret = 1;
		}

		return ret;
	}

	pair<int, int> find_pair(vector< pair<int, int> > v, int vertex) {
		for (int i = 0; i < v.size(); ++i) {
			if(v[i].second == vertex) {
				return v[i];
			}
		}

		return make_pair(-1, -1);
	}

	int dijkstra(int v, int ve) {
		// create e clone with height INF and the beginning border with wight as 0
		priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair <int, int> > > pq;
		// vector< pair<int, int> > dist;
		pair<int, int> *dist = new pair<int, int>[MAX_SIZE];
		pair<int, int> temp, buff;

		temp = make_pair(-1, -1); // guarantee the problem will have an output

		// make an priority queue and insert the beginning vertex into it
		pq.push(make_pair(0, v));
		// dist.push(make_pair(0, v));

		for (int i = 0; i < MAX_SIZE; ++i) {
			// if(e[i].size() > 0) {
				// dist.push_back(make_pair(INF, i));
				dist[i] = make_pair(INF, i);
			// }
		}
		update_w(dist, 0, v);

		while(!pq.empty()) {
			// get vertex weight
			// temp = find_pair(dist, pq.top().second);
			temp = dist[pq.top().second];

			// add the new vertex into the pq
			for (int i = 0; i < e[pq.top().second].size(); ++i) {
				
				int new_w = e[pq.top().second][i].first + pq.top().first;
				
				if(update_w(dist, new_w, e[pq.top().second][i].second)) { // update if new weight is lower
					// temp = find_pair(dist, e[pq.top().second][i].second);
					temp = dist[e[pq.top().second][i].second];
					pq.push(temp);
				}
			}

			pq.pop();
		}

		temp = dist[ve];
		return temp.first;
	}
};


int main(int argc, char const *argv[]) {
	ios::sync_with_stdio(0);
	int m, n;
	int a, b, w;
	int begin_v = 0, end_v;
	int tc, temp = -1;

	graph g;

	cin >> tc;

	// while(cin >> m >> n, m != 0 && n != 0) {
	for(; tc > 0;tc--) {
		
		cin >> m >> n >> begin_v >> end_v;

		for (int i = 0; i < n; ++i) {
			cin >> a >> b >> w;
			g.add_e(a, b, w);	
			// cout << "a: " << a << " b: " << b << " w: " << w << endl;
		}
		
		temp = g.dijkstra(begin_v, end_v);

		if(temp == INF || temp == -1) {
			cout << "NONE" << endl;
		}
		else {
			cout << temp << endl;
		}

		g.clean();
	}
 
	// g.print_e();
	// g.dijkstra(begin_v);

	return 0;
}