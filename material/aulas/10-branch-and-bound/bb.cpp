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

int M(int N, vector<int> &P, vector<int> &V, int C, int i, vector<bool> &used,
        vector<bool> &best, int &num_leaf, int &num_copy, vector<bool> &aux) {
    
    int valorUsed = 0, valorBest = 0;

    if (i == N) {
        num_leaf++;

        for(int i = 0; i < N; i++) {
            if(used[i]) valorUsed += V[i];
            if (best[i]) valorBest += V[i];
        }

        if (valorUsed > valorBest) {
            best = used;
            num_copy++;
        }

        return 0;
    }

    aux = used;
    for (int j = i; j < N; j++) {
        aux[j] = true;
    }
    
    int valorAux = 0;
    for (int i = 0; i < N; i++) {
        if (aux[i]) valorAux += V[i];

        if (best[i]) valorBest += V[i];
    }

    if (valorAux < valorBest) return 0;

    used[i] = false;
    int semItem, comItem;

    semItem = M(N, P, V, C, i+1, used, best, num_leaf, num_copy, aux);
    if (C - P[i] >= 0) {
        used[i] = true;
        comItem = M(N, P, V, C - P[i], i+1, used, best, num_leaf, num_copy, aux) + V[i];
        return max(semItem, comItem);
    }

    return semItem;
}


int main()  {

    int n, C;
    vector<int>  peso;
    vector<int>  valor;
    vector<bool> used;
    vector<bool> best;
    vector<bool> aux;
    int num_leaf = 0; // conta quantas vezes uma solução completa foi comparada com a melhor possível
    int num_copy = 0; // conta quantas vezes foi encontrada uma solução melhor que a atual 
    
    cin >> n >> C;

    peso.resize(n);
    valor.resize(n);
    used.resize(n, false);
    best.resize(n, false);
    aux.resize(n, false);

    int p, v;
    for (int i = 0; i < n; i++) {
        cin >> p >> v;
        peso[i] = p;
        valor[i] = v;
    }

    int value = M(n, peso, valor, C, 0, used, best, num_leaf, num_copy, aux);

    int wTotal = 0;
    for (int i = 0; i < n; i++) {
        if (best[i]) {
            wTotal += peso[i];
        }
    }

    cout << wTotal << " " << value << " " << '1' << "\n";

    for (int i = 0; i < n; i++) {
        if (best[i]) {
            cout << i << " ";
        }
    }

    cout << endl;
    return 0;
}
