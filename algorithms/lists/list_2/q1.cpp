#include <bits/stdc++.h>

using namespace std;

int main() {
    map< int, pair<int, int> > fox_list; // a map to connection and id
    list<list<int>> colisions; // list with all the id colisions
    
    int links, cookies, fox, a, b, ct = 1;
    int loop_break = 0;
    list<int> tmp_list;
    
    scanf(" %d %d", &fox, &links);
    
    cookies = fox;
    
    for (int i = 0; i < links; i++) {
        
        scanf(" %d %d", &a, &b);
        // printf("%d %d\n", fox_list[a], fox_list[b]);
        if(fox_list[a].first == 0 && fox_list[b] == 0) {
            fox_list[a].first = 1;
            fox_list[b].first = 1;
            fox_list[a].second = ct;
            fox_list[b].second = ct;
            ct++; // new disonex component in graph
        }
        
        else if(fox_list[a].first == 0 && fox_list[b].first == 1) {
            fox_list[a].second = fox_list[b].second;
            fox_list[a].first = 1;
        }
        
        else if(fox_list[a].first == 1 && fox_list[b].first == 0) {
            fox_list[b].second = fox_list[a].second;
            fox_list[b].first = 1;
        }
        
        else if(fox_list[a].first == 1 && fox_list[b].first == 1) {
            // link two graph componnent
            // Resolve colisão
            if(fox_list[a].second == fox_list[b].second) {
                continue;
            }
            for (int j = 0; j < colisions.size(); j++) {
                tmp_list = colisions.at(j);
                for (int k = 0; k < tmp_list.size(); k++) {
                    
                }
            }
        }
        
        
    }
    
    printf("%d\n", cookies);
    
}