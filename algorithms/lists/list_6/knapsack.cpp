#include <bits/stdc++.h>

#define MAX_SIZE 2001
#define endl "\n"

using namespace std;

int bag(pair<int, int> w[MAX_SIZE], int s, int n) {
    int a = 0, b = 0;
    int dp[MAX_SIZE][MAX_SIZE];
    for(int i = 0; i < s; i++) {
        for(int j = 0; j < n; j++) {
            dp[j][i] = 0;
        }
    }
    
    for(int i = 1; i <= s; i++) { // iters at every capacity
        for(int j = 0; j < n; j++) { // iters at every value
            a = b= 0;
            if(w[j].first <= i) {
                a = w[j].second;
            }
            if(j > 0) {
                b = dp[j - 1][i];
                
                if(w[j].first <= i) {
                    a = max(a, dp[j - 1][i - w[j].first] + w[j].second);
                }
            }
            
            dp[j][i] = max(a, b);
        }
    }
    
    return dp[n - 1][s];
}

int main() {
    ios::sync_with_stdio(0);
    
    int s, n;
    pair<int, int> w[MAX_SIZE];
    int res = 0;
    
    cin >> s >> n; // s is the capacity
    
    for(int i = 0; i < n; i++) {
        cin >> w[i].first >> w[i].second;
    }
    
    sort(w, w + n);
    
    res = bag(w, s, n);
    
    cout << res << endl;

    return 0;
}