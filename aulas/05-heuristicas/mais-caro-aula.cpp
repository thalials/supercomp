#include <iostream>
#include <algorithm>
#include <vector>

struct objeto {
    int peso, valor, id;

    bool operator <(objeto &a) {
        return valor > a.valor;
    }
};

// bool compara_objetos(objeto a, objeto b) {
//     return a.valor > b.valor;
// }

int main () {
    int N, peso_maximo;
    std::cin >> N >> peso_maximo;
    std::vector<objeto> objetos(N);
    std::vector<bool> usados(N, false);

    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        std::cin >> objetos[i].peso >> objetos[i].valor;
    }

    // std::sort(objetos.begin(), objetos.end());

    int peso_atual = 0;
    int valor_atual = 0;
    for (auto &obj : objetos) {
        if (peso_atual + obj.peso <= peso_maximo) {
            peso_atual += obj.peso;
            valor_atual += obj.valor;
            usados[obj.id] = true;
        }
    }
    
    std::cout << peso_atual << " " << valor_atual << "\n";
    for (int i = 0; i < N; i++) {
        if (usados[i]) 
            std::cout << i << " ";
    }
    std::cout << "\n";

    return 0;
}