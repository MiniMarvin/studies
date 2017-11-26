#include <bits/stdc++.h>

#define inf 0x3f3f3f3f
#define pii pair<int, int>
#define MAX_SIZE 1000

using namespace std;

class graph {
public:
    
    int nv;
    vector<pii> e[MAX_SIZE];
    int v[MAX_SIZE];
    
    graph(){
        this->nv = 0;
    }
    
    ~graph(){}
    
    void add_e(int a, int b, int w) {
        this->e[a].push_back(make_pair(w, b));
        this->e[b].push_back(make_pair(w, a));
        
        if(!v[a])
            this->nv++;
        if(!v[b])
            this->nv++;
            
        v[a] = v[b] = 1;
    }
    
    void prim() {
        priority_queue< pii, vector<pii>, greater<pii> > lst;
        pii mst[MAX_SIZE];
        vector<pii> w_v;
        pii aux;
        
        
        for(int i = 0; i < MAX_SIZE; i++) {
            mst[i] = make_pair(0, -1);
        }
        
        for(int j = 0, i = 0; i < nv; j++) {
            if(e[j].size() > 0) {
                w_v.push_back(make_pair(inf, i));
                
                for(int k = 0; k < e[k].size() && i == 0; k++) {
                    mst[ e[i][k].second ].second = j;
                    lst.push(e[i][k]);
                }
                i++;
            }
        }
        
        mst[w_v[0].second].first = 1;
        w_v[0].first = 0;
        
        while(!lst.empty()) {
            aux = lst.top();
            lst.pop();
            
            cout << aux.second << ", " << aux.first << endl;
            
            if(mst[aux.second].first) {
                continue;
            }
            
            for(int i = 0; i < e[aux.second].size(); i++) {
                lst.push(e[aux.second][i]);
                mst[ e[aux.second][i].second ].second = aux.second;
                cout << "Adding:" << e[aux.second][i].second << ", " << e[aux.second][i].first << endl;
            }
            
            // update the weight
            for(int i = 0; i < MAX_SIZE; i++) {
                if(w_v[i].second == aux.second) {
                    cout << "old w: " << w_v[i].first << " ";
                    if(mst[aux.second].second != -1) {
                        w_v[i].first = min(w_v[i].first, 
                                            w_v[mst[i].second].first + aux.first);
                    }
                    else {
                        w_v[i].first = min(w_v[i].first, 0);
                    }
                
                    cout << "new w: " << w_v[i].first << endl;
                    break;
                }
            }
            
            mst[aux.second].first = 1;
        }
        
        for(int i = 0; i < nv; i++) {
            cout << w_v[i].second << ", " << w_v[i].first  << endl;
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
    
    ios::sync_with_stdio(0);
    graph g;
    
    int n, a, b, w, mst;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cin >> a >> b >> w;
        g.add_e(a, b, w);
    }
    
    g.prim();
    
    return 0;
}