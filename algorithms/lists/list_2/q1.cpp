// 1 - visited by insertion
// 2 - visited by analysis

#include <bits/stdc++.h>

using namespace std;

int main() {
    map< int, pair<int, int> > fox_list; // a map to if is connected and id
    map< int, pair<int, int> > colisions; // collect pair and the connection list
    
    int links, cookies, fox, a, b, ct = 1;
    int buff;
    map< int, pair<int, int> >::iterator it;
    pair< int, int > pt;
    int now_ct;
    
    scanf(" %d %d", &fox, &links);
    
    cookies = fox;
    
    for (int i = 0; i < links; i++) {
        
        scanf(" %d %d", &a, &b);
        // printf("%d %d\n", fox_list[a], fox_list[b]);
        if(fox_list[a].first == 0 && fox_list[b].first == 0) {
            fox_list[a].first = 1;
            fox_list[b].first = 1;
            fox_list[a].second = ct;
            fox_list[b].second = ct;
            colisions[ct].first = 1;
            colisions[ct].second = ct;
            ct++; // new disonex component in graph
            cookies--;
        }
        
        else if(fox_list[a].first == 0 && fox_list[b].first == 1) {
            fox_list[a].second = fox_list[b].second;
            fox_list[a].first = 1;
            cookies--;
        }
        
        else if(fox_list[a].first == 1 && fox_list[b].first == 0) {
            fox_list[b].second = fox_list[a].second;
            fox_list[b].first = 1;
            cookies--;
        }
        
        else if(fox_list[a].first == 1 && fox_list[b].first == 1) {
            // link two graph componnent
            // Resolve colisão
            if(fox_list[a].second == fox_list[b].second) {
                continue;
            }
            else {
                // map[a] == a?
                int menor, maior;
                
                // pega o menor
                if(fox_list[b].second < fox_list[a].second) {
                    menor = fox_list[b].second;
                    maior = fox_list[a].second;
                }
                else {
                    menor = fox_list[a].second;
                    maior = fox_list[b].second;
                }
                
                // TODO: toda vez que uma colisão for detectada fazer a busca para saber se ela já foi contada, se não
                // subtrai 1 em cookies
                
                // faz uma busca por um elemento do grafo cujo a classe ainda não tenha sido visitada
                if(colisions[menor].second == menor) {
                    colisions[menor].second = maior;
                }
                else {
                    buff = colisions[menor].second;
                    
                    // já existia essa colisão
                    if(buff != maior) {
                        colisions[menor].second = maior;
                        colisions[maior].second = buff;
                    }
                }
            }
        }
    }
    
    
    // conta todas as colisões
    // for(it = colisions.begin(); it != colisions.end(); it++) {
    //     pt = it->second;
        
    //     if(pt.first == 2) { // have been counted already
    //         continue;
    //     }
        
    //     now_ct = it->first;
    //     colisions[now_ct].first = 2; // make the map change
        
    //     while(pt.second != it->first) {
    //         colisions[now_ct].first = 2; // make the map change
    //         now_ct = pt.second;
    //         pt = colisions[pt.second]; // next element
    //         cookies--;
    //     }
    // }
    
    printf("%d\n", cookies);
    
}