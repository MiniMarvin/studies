#include <bits/stdc++.h>

#define inf 0x3f3f3f3f
#define MAX_SIZE 100

using namespace std;

//int coin(int *coin_set, int* dp[], int val, int n) {
int coin(int *coin_set, int dp[MAX_SIZE][MAX_SIZE], int val, int n) {
    int a = inf, b = inf;
    
    for(int i = 1; i <= val; i++) { // iters in every value
        for(int j = 0; j < n; j++) { // iters at every coin set
            a = b = inf;
            if(j > 0) {
                a = dp[j-1][i];
            }
            if(i >= coin_set[j]) {
                b = 1 + dp[j][i - coin_set[j]];
            }
            /*if(min(a,b) > 0) dp[i][j] = min(a,b);
            else dp[i][j] = max(a,b);*/
            dp[j][i] = min(a,b);
            cout << dp[j][i] << " ";
        }
        cout << endl;
    }
    
    return dp[n - 1][val];
}

void print_arr(int *arr, int sz) {
    for(int i = 0; i < sz; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    
    int n = 0; // number of coins
    int val = 0; // value of searched coin
    int r = 0; 
    int *coin_set, dp[MAX_SIZE][MAX_SIZE];
    
    cin >> n;
    coin_set = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> coin_set[i];
    }
    cin >> val;
    
    sort(coin_set, coin_set + n);
    
    // build DP array
    for(int i = 0; i < n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= val; j++) {
            dp[i][j] = inf;
        }
    }
    
    r = coin(coin_set, dp, val, n);
    cout << r << endl;
    return 0;
}