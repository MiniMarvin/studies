#include <bits/stdc++.h>

#define inf 0x3f3f3f3f
#define MAX_SIZE 1000
#define endl "\n"

using namespace std;

class graph{
public:
    // variables
    vector< pair<int, int> > e[MAX_SIZE];
    vector<int> v;
    int max_v;

    graph(){
        this->max_v = 0;
    }
    ~graph(){}
    
    void add_e(int a, int b, int w) {
        this->e[a].push_back(make_pair(w, b));
        this->e[b].push_back(make_pair(w, a));
        bool check_a = false, check_b = false;
        
        for(int i = 0; i < v.size(); i++) {
            if(check_a&&check_b) break;
            if(v[i] == a) check_a = true;
            if(v[i] == b) check_b = true;
        }
        
        if(!check_a) v.push_back(a);
        if(!check_b) v.push_back(b);
        
        if(a > max_v) max_v = a;
        if(b > max_v) max_v = b;
    }
    
    int prim() {
        int mst = 0;
        int arr_v[max_v];
        pair<int, int> aux;
        memset(arr_v, 0, sizeof(int)*max_v);
        
        // at every node goes adding the edges to the priority queue
        priority_queue<pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > to_check;
        
        for(int i = 0; i < MAX_SIZE; i++) { // get the first vertex and mark it
            if(this->e[i].size() > 0) {
                for(int j = 0; j < this->e[i].size(); j++) {
                    to_check.push(e[i][j]);
                    cout << "adding: ";
                    cout << this->e[i][j].second << ", " << this->e[i][j].first << endl;
                }
                arr_v[i] = 1;
                break;
            }
        }
        
        while(!to_check.empty()) { // while have something to check in the priority queue
            cout << to_check.top().second << ", " << to_check.top().first << endl;
            
            aux = to_check.top();
            to_check.pop();
            
            if(arr_v[to_check.top().second] == 1) { // if already visited that node just goes on
                // to_check.pop();
                continue;
            }
            
            
            arr_v[aux.second] = 1; // mark as visited
            
            for(int i = 0; i < e[aux.second].size(); i++) {
                cout << "adding: ";
                cout << this->e[aux.second][i].second << ", " << this->e[aux.second][i].first << endl;
                to_check.push(e[aux.second][i]);
            }
            
            // add to the mst
            mst += aux.first;
            
        }
        
        return mst;
    }
    
    void print_edges() {
        for(int i = 0; i < MAX_SIZE; i++) {
            if(e[i].size() > 0) {
                cout << "vertex " << i << " has: ";
                for(int j = 0; j < e[i].size(); j++) {
                    cout << "(" << e[i][j].second << ", " << e[i][j].first << ") ";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    
    graph g;
    int n, a, b, w, mst;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cin >> a >> b >> w;
        g.add_e(a, b, w);
    }
    
    g.print_edges();
    
    mst = g.prim();
    
    cout << mst << endl;
    
    return 0;
}