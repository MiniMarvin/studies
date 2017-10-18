#include <bits/stdc++.h>

using namespace std;

void randomize(unsigned a,unsigned b,unsigned mod, unsigned *arr);
void quicksort(unsigned *arr, unsigned begin, unsigned end);

void swap(unsigned &a, unsigned &b) {
    int t = a;
    a = b;
    b = t;
}

int main() {
    
    unsigned *arr = new unsigned[5000000];
    unsigned a, b, mod, k;
    
    scanf(" %d %d %d %d", &a, &b, &mod, &k);

    randomize(a, b, mod, arr);
    
    
    
    printf("%d\n", arr[k]);
    
    delete arr;
    
    return 0;
}


void randomize(unsigned a, unsigned b, unsigned mod, unsigned *arr) {
    for( int i=0 ; i<5000000 ; i++ ) {
        a = 31014 * (a & 65535) + (a >> 16);
        b = 17508 * (b & 65535) + (b >> 16);
        arr[i] = ((a << 16) + b) % mod;
    }
}


int splitarr(unsigned *arr, unsigned begin, unsigned end) {
    unsigned pivot = arr[pos];
    int i = 0, j = end - begin;
    
    swap(arr[0], arr[pos])
    
    while(i < j) {
        
        for(i; arr[i] < pivot && i < sz; i++);
        for(j; arr[j] > pivot && j > 0; j--);
        
        if( i < j ) {
            swap(arr[i], arr[j]);
        }
        
    }
    
    swap(arr[0], arr[j]);
    
    return j;
}

unsigned smartquick(unsigned *arr, unsigned begin, unsigned end, unsigned k) {
    
    unsigned val;
    
    if(begin > end) 
        return arr[k];
    
    val = splitarr(arr, begin, end);
    if(k > val) smartquick(arr, val + 1, end, k);
    else if(k < val) smartquick(arr, begin, val - 1, k);
    
    return arr[k];
}