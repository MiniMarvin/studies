#include <bits/stdc++.h>

#define inf 0x3f3f3f3f
#define endl "\n"
#define pii pair<int, int>
#define MAX_SIZE 1000

using namespace std;

class graph{
public:

    vector<pii> e[MAX_SIZE];
    vector<int> v;

    graph(){}
    ~graph(){}
    
    void add_e(int a, int b, int w) {
        this->e[a].push_back(make_pair(w, b));
        this->e[b].push_back(make_pair(w, a));
        
        bool adda = true, addb = true;
        
        for(int i = 0; i < v.size(); i++) {
            if(v[i] == a) adda = false;
            if(v[i] == b) addb = false;
            if(!adda && !addb) break;
        }
        
        if(adda) v.push_back(a);
        if(addb) v.push_back(b);
    }
    
    void prim() {
        priority_queue< pii, vector<pii>, greater<pii> > lst;
        int vt[MAX_SIZE] = {0};
        int w[MAX_SIZE];
        int parent[MAX_SIZE] = {-1}; // all the vertex parents
        vector<pair<int, pair<int ,int> > > mst;
        pii aux;
        
        
        memset(w, inf, MAX_SIZE);
        
        for(int i = 0; i < MAX_SIZE; i++) {
            if(e[i].size() > 0) {
                vt[i] = 1;
                w[i] = 0;
                
                for (int j = 0; j < e[i].size(); j++) {
                    lst.push(e[i][j]);
                    parent[e[i][j].second] = i;
                }
                
                break;
            }
        }
        
        while(!lst.empty()) {
            aux = lst.top();
            lst.pop();
            
            if(vt[aux.second]) continue;
            
            // w[aux.second] = min(w[parent[aux.second]] + aux.first, w[aux.second]);
            w[aux.second] = w[parent[aux.second]] + aux.first; // update weight
            
            mst.push_back(make_pair(aux.first, make_pair(parent[aux.second], aux.second)));
            vt[aux.second] = 1;
            
            for(int i = 0; i < e[aux.second].size(); i++) {
                lst.push(e[aux.second][i]);
                parent[e[aux.second][i].second] = aux.second;
            }
            
        }
        
        cout << "mst:" << endl;
        for(int i = 0; i < mst.size(); i++) {
            cout << mst[i].second.first << ", " << mst[i].second.second << ", " << mst[i].first << endl;
        }
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
    
    graph g;
    
    int n, a, b, w, mst;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cin >> a >> b >> w;
        g.add_e(a, b, w);
    }
    
    g.print_edges();
    g.prim();
    
    return 0;
}