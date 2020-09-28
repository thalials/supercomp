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

long num_hit = 0, num_copy = 0, num_bound = 0;

int busca_exaustiva(std::vector<objeto> &obj, int C, solucao &melhor, solucao &atual, int i = 0) {
    if (i == obj.size()) {
        num_hit++;
        if (atual.valor > melhor.valor) {
            std::cerr << "Encontrou melhor:" << melhor.valor << " para " << atual.valor << "\n";
            melhor = atual;
            num_copy++;
        }
        return atual.valor;
    }

    int com, sem;
    sem = busca_exaustiva(obj, C, melhor, atual, i+1);
    if (obj[i].peso <= C) {
        atual.add_objeto(obj[i]);
        com = busca_exaustiva(obj, C - obj[i].peso, melhor, atual, i+1);
        atual.tira_objeto(obj[i]);
    }

    return (com > sem)? com : sem;
}

int main() {
    int N, W;
    std::cin >> N >> W;
    std::vector<objeto> objetos(N);
    
    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        std::cin >> objetos[i].peso >> objetos[i].valor;
    }

    solucao melhor(N);
    solucao atual(N);
    busca_exaustiva(objetos, W, melhor, atual);

    std::cout << melhor.peso << " " << melhor.valor << " 1\n";
    for (int i = 0; i < N; i++) {
        if (melhor.usado[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
    std::cerr << "num_hit: " << num_hit << " num_copy " << num_copy << " num_bound: " << num_bound << "\n";

    return 0;
}