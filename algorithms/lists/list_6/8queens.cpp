#include <bits/stdc++.h>

#define in 0x3f3f3f3f
#define BOARD_SIZE 9

using namespace std;

int g_ct = 0;

int detect_colision(int col, int fcol, int sol[], int sz) {
    int x1, x2, y1, y2, d1, d2;
    // Detecta colisão ------------------------------------------------------------------------------
    // verifica se ocorreu alguma colisão até o momento
    // não precisa verificar na mesma coluna, pois, o controle do iterador é por colunas
    // verifica se tinha alguem que não seja ele mesmo na mesma linha
    for(int i = 1; i < sz; i++) {
        if(i == col) continue;
        if(sol[i] == sol[col]) return 1;
    }
    // verifica se tinha alguem que não seja ele mesmo na mesma diagonal
    int mat[sz + 1][sz + 1];
    
    for(int i = 0; i <= sz; i++) {
        for(int j = 0; j <= sz; j++) {
            mat[i][j] = 0;
        }
    }
    
    // gera a matriz de posições
    for(int i = 1; i < sz; i++) { // itera nas colunas
        mat[sol[i]][i] = 1;
        mat[0][i] = 0;
    }
    // recupera as duas diagonais a percorrer
    for(x1 = col, y1 = sol[col]; x1 > 1 && y1 > 1; x1--, y1--); // diagonal para cima
    for(x2 = col, y2 = sol[col]; x2 > 1 && y2 < sz; x2--, y2++); // diagonal para baixo
    
    // percorre a primeira diagonal
    d1 = d2 = 0;
    for(; x1 < sz && y1 < sz; x1++, y1++) { // diagonal para cima
        d1 += mat[y1][x1];
    }
    // percorre a segunda diagonal
    for(; x2 < sz && y2 >= 1; x2++, y2--) { // diagonal para cima
        d2 += mat[y2][x2];
    }
    
    if(d1 > 1 || d2 > 1) { // encontrou uma colisão na diagonal
        return 1;
    }
    
    return 0;
    //-----------------------------------------------------------------------------------------------
}

// algorithm: put the queen in a row over the column, verify if the the queen can be there, if not, return 0, if can goes on into the recursion
// on the end of the recursion them it returns 1 and the solution matrix is done, on the error of the solution matrix, clean it's position and return
// at every iteration there's a counter into it
// obs: necessary to define the first column
// obs: I'm doing the col 1 in the param col = 0
int queens(int col, int fcol, int sol[], int sz) {
    int res = 0;
    int x1, x2, y1, y2, d1, d2;
    int aux = 0;
    
    if(col == fcol) { // está na coluna inicial
        // pula para a próxima coluna
        col++;
    }
    
    if(col == sz) { // preencheu todas as colunas
        res = 1;
        g_ct++;
        if(g_ct < 10) {
            cout << " ";
        }
        cout << g_ct << "      ";
        
        for(int j = 1; j < BOARD_SIZE - 1; j++) {
            cout << sol[j] << " ";
        }
        cout << sol[BOARD_SIZE - 1];
        cout << endl;
        
        return 0;
        //return res;
    }
    
    int mat[sz][sz];
    
    for(int i = 1; i < sz; i++) {
        sol[col] = i;
        aux = detect_colision(col, fcol, sol, sz);
        
        if(aux) {
            sol[col] = 0;
        }
        else {
            res = queens(col + 1, fcol, sol, sz);
            if(res) {
                // break;
                g_ct++;
                sol[col] = 0;
            }
            else {
                sol[col] = 0;
            }
        }
        
    }
    
    return res; // se terminou tudo então a solução para essa coluna está definida
}

int main() {
    int n;
    int r, c, fcol;
    int rows = BOARD_SIZE, cols = BOARD_SIZE;
    
    int *sol = new int[rows];
    memset(sol, 0, sizeof(int)*rows);
    
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> r >> c;
        sol[c] = r;
        
        cout << "SOLN       COLUMN" << endl;
        cout << " #      1 2 3 4 5 6 7 8" << endl << endl;
        
        queens(1, c, sol, 9);
        if(i != n - 1)
            cout << endl;
        g_ct = 0;
        memset(sol, 0, sizeof(int)*rows);
    }
    
    return 0;
}