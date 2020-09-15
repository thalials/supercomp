#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct objeto {
    int id;
    int peso;
    int valor;
    bool usado;
};

int main() {
    int N, W;
    std::cin >> N >> W;
    std::vector<objeto> objetos(N);
    
    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        objetos[i].usado = false;
        std::cin >> objetos[i].peso >> objetos[i].valor;
    }

    int peso = 0;
    int valor = 0;
    std::vector<int> resposta;
    resposta.reserve(N);

    std::sort(objetos.begin(), objetos.end(), [](objeto &a, objeto &b) {
        return a.valor > b.valor;
    });
    int i = 0;
    std::default_random_engine eng(20);
    std::uniform_real_distribution<double> heuristica(0, 1); 
    while (i < N) {
        int idx;
        if (heuristica(eng) <= 0.25) {
            std::uniform_int_distribution<int> proximo(i, N-1);
            idx = proximo(eng);
            while(objetos[idx].usado)
                idx = proximo(eng);

        } else {
            idx = i++;
        }

        auto &o = objetos[idx];
        if (!o.usado && peso + o.peso < W) {
            o.usado = true;
            resposta.push_back(o.id);
            peso += o.peso;
            valor += o.valor;
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