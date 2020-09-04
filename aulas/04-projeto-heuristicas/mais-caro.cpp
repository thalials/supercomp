#include <iostream>
#include <algorithm>
#include <vector>

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

    std::sort(objetos.begin(), objetos.end(), [](objeto &a, objeto &b) {
        return a.valor > b.valor;
    });

    int peso = 0;
    int valor = 0;
    std::vector<int> resposta;
    resposta.reserve(N);

    for (objeto &o : objetos) {
        if (peso + o.peso < W) {
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