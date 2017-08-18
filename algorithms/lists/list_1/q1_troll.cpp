#include <iostream>

using namespace std;

int main() {
    long int list[1000000];
    
    int in, action, value, ct = 0;
    
    cin >> in;
    
    for (int i = 0; i < in; i++) {
        
        cin >> action;
        if(action == 1) {
            ct++;
            cin >> value;
            list[ct] = value;
        }
        
        else if(action == 2) {
            if(ct > 0){
                list[ct-1] = list[ct];
                ct--;
            }
        }
        
        else if(action == 3) {
            if(ct > 0) {
                cout << list[ct] << endl;
            }
            else {
                cout << "Empty!" << endl;
            }
        }
    }
}