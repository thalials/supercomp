#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cassert>

struct objeto {
    int id;
    int peso;
    int valor;
};

struct solucao {
    std::vector<double> usado;
    double valor;
    double peso;

    solucao(int N) {
        usado.resize(N, 0);
        valor = peso = 0;
    }

    void add_objeto(objeto &o, double fracao=1) {
        usado[o.id] = fracao;
        peso += o.peso * fracao;
        valor += o.valor * fracao;
    }

    void tira_objeto(objeto &o) {
        peso -= o.peso;
        valor -= o.valor;
        usado[o.id] = 0;
    }
};

int main() {
    int N, W;
    std::cin >> N >> W;
    std::vector<objeto> objetos(N);

    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        std::cin >> objetos[i].peso >> objetos[i].valor;
    }

    std::sort(objetos.begin(), objetos.end(), [](auto &a, auto &b) -> bool {
        return double(a.valor) / a.peso > double(b.valor) / b.peso;
    });

    solucao fracionaria(N);
    for (objeto &o : objetos) {
        if (o.peso + fracionaria.peso <= W) {
            fracionaria.add_objeto(o);
        } else if (fracionaria.peso < W) {
            double capacidade_sobrando = W - fracionaria.peso;
            fracionaria.add_objeto(o, capacidade_sobrando / o.peso);
        }
    }


    std::cout << fracionaria.peso << " " << fracionaria.valor << " 1\n";
    for (int i = 0; i < N; i++) {
        std::cout << "(" << fracionaria.usado[i] << ") ";
    }
    std::cout << "\n";
    return 0;
}
