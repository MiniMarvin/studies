// OBS: NÃO UTILIZAR UM PIVOT DIFERENTE DE ZERO, POIS, HÁ UM ERRO NO CASO:
// 1 1 1 1 -1 -2 -3 1 1 1 1 1 0 0

#include <bits/stdc++.h>

using namespace std;

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

void print_arr(int* arr, int begin, int end) {
    for(int i = begin; i < end; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void quick_split(int* arr, int begin, int end);

int main() {
    
    int *mlist, sz, menor = 0;
    
    cin >> sz;
    mlist = new int[sz];
    for(int i = 0; i < sz; i++) {
        cin >> mlist[i];
    }
    
    swap(mlist[0], mlist[menor]);
    
    quick_split(mlist, 0, sz);
    print_arr(mlist, 0, sz);
}


void quick_split(int* arr, int begin, int end) {
    int i = begin, j = end - 1, pivot = 0;
    while(i < j) {
        for(; arr[i] < pivot && i < end; i++);
        for(; arr[j] > pivot && j > begin; j--);
        if(i < j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
}