#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct objeto {
    int id;
    int peso;
    int valor;
};

struct solucao {
    std::vector<bool> usado;
    int valor;
    int peso;

    solucao(int N) {
        usado.resize(N, false);
        valor = peso = 0;
    }

    void add_objeto(objeto &o) {
        usado[o.id] = true;
        peso += o.peso;
        valor += o.valor;
    }

    void tira_objeto(objeto &o) {
        peso -= o.peso;
        valor -= o.valor;
        usado[o.id] = false;
    }
};

int num_hit = 0, num_bound = 0;

int bound(std::vector<objeto> &obj, int i) {
    int valor_extra = 0;
    for (i; i < obj.size(); i++) {
        valor_extra += obj[i].valor;
    }
    return valor_extra;
}

void busca_exaustiva(std::vector<objeto> &obj, int C, solucao &melhor, solucao &atual, std::vector<int> &bounds, int i = 0) {
    if (i == obj.size()) {
        num_hit++;
        if (atual.valor > melhor.valor) {
            std::cerr << "Encontrou melhor:" << melhor.valor << " para " << atual.valor << "\n";
            melhor = atual;
        }
        return;
    }

    if (atual.valor + bounds[i] < melhor.valor) {
        num_bound++;
        return;
    }

    if (obj[i].peso <= C) {
        atual.add_objeto(obj[i]);
        busca_exaustiva(obj, C - obj[i].peso, melhor, atual, bounds, i+1);
        atual.tira_objeto(obj[i]);
    }
    busca_exaustiva(obj, C, melhor, atual, bounds, i+1);
}

int main() {
    int N, W;
    std::cin >> N >> W;
    std::vector<objeto> objetos(N);
    std::vector<int> bounds(N, 0);
    
    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        std::cin >> objetos[i].peso >> objetos[i].valor;
    }

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            bounds[i] += objetos[j].valor;
        }
    }

    solucao melhor(N);
    solucao atual(N);
    busca_exaustiva(objetos, W, melhor, atual, bounds);

    std::cout << melhor.peso << " " << melhor.valor << " 1\n";
    for (int i = 0; i < N; i++) {
        if (melhor.usado[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
    std::cerr << "num_hit: " << num_hit << " num_bound: " << num_bound << "\n";

    return 0;
}