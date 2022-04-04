#include <iostream>
#include <math.h>
#include <algorithm> // sort
#include <vector>

using namespace std;

// entrada -> peso e valor 
//             w       v
struct item {
    int id;
    int valor;
    int peso;
};

// ordena pelo maior valor (ordem decrescente)
void mais_caro(vector<item> &items) {
    sort(items.begin(), items.end(), [](const item &a, const item &b) {
        return a.valor > b.valor;
    });
}

void mais_leve(vector<item> &items) {
    sort(items.begin(), items.end(), [](const item &a, const item &b) {
        return a.peso < b.peso;
    });
}

int main() {
    int T = 0;                    // Numero de objetos selecionados 
    int peso_atual = 0;           // peso atual na mochila
    int valor_atual = 0;          // valor atual na mochila
    vector<int> resposta;

    int N, W;
    cin >> N >> W;
    //cout << "N: " << N << endl;
    //cout << "W: " << W << endl;
    
    vector<item> items;
    resposta.resize(N);

    for (int i=0; i < N; i++) {
        item current_item;
        current_item.id = i;
        cin >> current_item.peso;        
        cin >> current_item.valor;

        items.push_back(current_item);
    }

    //mais_caro(items);
    mais_leve(items);

    for (int i=0; i < N; i++) {
        if (peso_atual + items[i].peso <= W) {
            resposta[T] = items[i].id;
            peso_atual += items[i].peso;
            valor_atual += items[i].valor;
            T++;
        }
     }
    cout << peso_atual << " " << valor_atual << " " << "0" << endl;
    
    for (int i = 0; i < T; i++) {
        cout << resposta[i] << " ";
    }

    cout << endl;
    return 0;
}