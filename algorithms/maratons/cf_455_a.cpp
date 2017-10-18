#include <bits/stdc++.h>

using namespace std;

bool sort_pair(pair<int, int> a, pair<int, int> b) {
    return (a.second > b.second);
}

int main() {
    
    int n, buff, total[100000] = {0}, ct = 0; // v-> the numbers to look up, total -> the sum
    pair<int, int>  v[100000]; // first the element and second it's sum
    int * marks;
    long long int max = 0, clone = 0, max_val = 0;
    
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        scanf("%d", &buff);
        
        if(total[buff] == 0) {
            v[ct] = make_pair(buff, 0);
            ct++;
        }
        
        max += buff;
        total[buff] += buff;
    }
    
    // Realiza um assign em v[]
    for (int i = 0; i < ct; i++) {
        v[i] = make_pair(v[i].first, total[v[i].first]);
    }
    
    // Realiza um assign em v[]
    for (int i = 0; i < ct; i++) {
        cout << v[i].first << " | " << v[i].second << endl;
    }
    cout << endl;
    
    sort(v, v + ct, sort_pair);
    
    // Realiza um assign em v[]
    for (int i = 0; i < ct; i++) {
        cout << v[i].first << " | " << v[i].second << endl;
    }
    
    cout << max << endl;
    
    // TODO: verificar quais deles estão marcados
    // verifica um a um quem tem a maior soma, como se fosse no bubble sort
    for(int i = 0; i < ct; i++) {
        
    }
    
    
    return 0;
}