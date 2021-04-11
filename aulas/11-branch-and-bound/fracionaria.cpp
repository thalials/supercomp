#include <iostream>
#include <algorithm>
#include <vector>

struct objeto {
    int peso, valor, id;

    bool operator <(objeto &a) {
        return double(valor)/peso > double(a.valor)/a.peso;
    }
};


int main () {
    int N, peso_maximo;
    std::cin >> N >> peso_maximo;
    std::vector<objeto> objetos(N);
    std::vector<double> usados(N, 0);

    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        std::cin >> objetos[i].peso >> objetos[i].valor;
    }

    std::sort(objetos.begin(), objetos.end());

    int peso_atual = 0;
    int valor_atual = 0;
    for (auto &obj : objetos) {
        if (peso_atual + obj.peso <= peso_maximo) {
            peso_atual += obj.peso;
            valor_atual += obj.valor;
            usados[obj.id] = 1.0;
        } else if (peso_atual < peso_maximo) {
            double frac = double(peso_maximo - peso_atual) / obj.peso;
            peso_atual += frac * obj.peso;
            valor_atual += frac * obj.valor;
            usados[obj.id] = frac;
        }
    }
    
    std::cout << peso_atual << " " << valor_atual << "\n";
    for (int i = 0; i < N; i++) {
        std::cout << usados[i] << " ";
    }
    std::cout << "\n";

    return 0;
}