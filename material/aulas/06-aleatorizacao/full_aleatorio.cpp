#include <iostream>
#include <math.h>
#include <algorithm> // sort
#include <vector>
#include <random>

using namespace std;

// entrada -> peso e valor 
//             w       v
struct item {
    int id;
    int valor;
    int peso;
    bool used;
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

void heuristica(vector<item> &items, int N, int W, int randomSeed) {
    int T = 0;
    int peso_atual = 0, valor_atual = 0;
    vector<int> resposta;

    resposta.resize(N);

    // probabilidade 
    default_random_engine generator;
    generator.seed(randomSeed);
    uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < N; i++) {
        double probabilidade = distribution(generator);
        //cout << "prob " << probabilidade << endl;
        if (probabilidade <= 0.5) {
            if (peso_atual + items[i].peso <= W) {
            resposta[T] = items[i].id;
            peso_atual += items[i].peso;
            valor_atual += items[i].valor;
            T++;
            }
        }
    }
    cout << peso_atual << " " << valor_atual << " " << "0" << endl;
    sort(resposta.begin(), resposta.begin() + T);

    for (int i = 0; i < T; i++) {
        cout << resposta[i] << " ";
    }

    cout << "\n";
}

int main() {
    vector<item> items;

    int N, W;
    cin >> N >> W;
    
    vector<int> resposta;
    resposta.resize(N);

    for (int i=0; i < N; i++) {
        item current_item;
        current_item.id = i;
        cin >> current_item.peso;        
        cin >> current_item.valor;

        items.push_back(current_item);
    }

    mais_caro(items);

    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, 10000);

    // heuristica
    for (int i = 0; i < 10; i++) {
        int randomSeed = distribution(generator);
        heuristica(items, N, W, randomSeed);
        cout << endl;
    }
    return 0;
}