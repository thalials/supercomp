#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct objeto {
    int id;
    int peso;
    int valor;
};

int main() {
    int N, W;
    std::cin >> N >> W;
    std::vector<objeto> objetos(N);
    
    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        std::cin >> objetos[i].peso >> objetos[i].valor;
    }

    int peso = 0;
    int valor = 0;
    std::vector<int> resposta;
    resposta.reserve(N);

    std::sort(objetos.begin(), objetos.end(), [](objeto &a, objeto &b) {
        return a.valor > b.valor;
    });

    std::vector<bool> usados(N, false);
    
    int i = 0; 
    std::default_random_engine eng(20);
    std::uniform_real_distribution<double> d(0.0, 1.0);
    while (i < N) {
        if (usados[i]) {
            i++;
            continue;
        };
        int idx;
        if (d(eng) < 0.25) {
            std::uniform_int_distribution<int> d_resto(i, N-1);
            idx = d_resto(eng);
        } else {
            idx = i;
            i++;
        }
        objeto *o = &objetos[idx];

        if (!usados[idx] && peso + o->peso < W) {
            usados[idx] = true;
            resposta.push_back(o->id);
            peso += o->peso;
            valor += o->valor;
            std::cerr << o->id << " " << o->peso << " " << o->valor << "\n";
        }
    }

    std::sort(resposta.begin(), resposta.end());
    std::cout << peso << " " << valor << " 0\n";
    for (int id : resposta) {
        std::cout << id << " ";
    }
    std::cout << "\n";

    return 0;
}