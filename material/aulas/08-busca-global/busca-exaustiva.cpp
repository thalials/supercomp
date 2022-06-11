#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// N - num de objs
// P - peso
// valor dos objetos
// C capacidade

/*  Pseudocódigo retornando o valor da mochila ótima
func(P, V, N, C, i) 
    se i=N
        return 0
    semItem = func(P, V, N, C, i+1)
    if (C - P[i] >= 0)
        comItem = mochila(P, V, N, C - P[i], i + 1) + V[i];
        return max(comItem, semItem) 
    
    return semItem
*/

int M(int N, vector<int> &P, vector<int> &V, int C, int i) {
    if (i == N) {
        return 0;
    }
    int semItem, comItem;

    semItem = M(N, P, V, C, i + 1);
    comItem = semItem;

    if (C - P[i] > 0) {
        comItem = M(N, P, V, C - P[i], i + 1) + V[i];
    }

    return max(semItem, comItem);
}


int main()  {

    int n, C;
    cin >> n >> C;

    vector<int> peso;
    peso.resize(n);

    vector<int> valor;
    valor.resize(n);

    for(int i=0; i < n; i++) {
        cin >> peso[i];
        cin >> valor[i];
    }

    cout << M(n, peso, valor, C, 0) << endl;
    
    return 0;
}