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
std::vector<long>bound_level;

double bound(std::vector<objeto> &obj, int i, int C) {
    double extra = 0.0;
    for (; i < obj.size(); i++) {
        objeto &o = obj[i];
        if (o.peso <= C) {
            extra += o.valor;
            C -= o.peso;
        } else {
            extra += o.valor * (double(C) / o.peso);
            break;
        }
    }
    return extra;
}

void busca_exaustiva(std::vector<objeto> &obj, int C, solucao &melhor, solucao &atual, int i = 0) {
    if (i == obj.size()) {
        num_hit++;
        if (atual.valor > melhor.valor) {
            std::cerr << "Encontrou melhor:" << melhor.valor << " para " << atual.valor << "\n";
            melhor = atual;
            num_copy++;
        }
        return;
    }

    if (atual.valor + bound(obj, i, C) < melhor.valor) {
        bound_level[i]++;
        num_bound++;
        return;
    }

    if (obj[i].peso <= C) {
        atual.add_objeto(obj[i]);
        busca_exaustiva(obj, C - obj[i].peso, melhor, atual, i+1);
        atual.tira_objeto(obj[i]);
    }
    busca_exaustiva(obj, C, melhor, atual, i+1);
}

int main() {
    int N, W;
    std::cin >> N >> W;
    std::vector<objeto> objetos(N);
    bound_level.resize(N, 0);

    
    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        std::cin >> objetos[i].peso >> objetos[i].valor;
    }

    std::sort(objetos.begin(), objetos.end(), [](auto &a, auto &b) -> bool {
        return double(a.valor) / a.peso > double(b.valor) / b.peso;
    });


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
    for (auto &i : bound_level) { 
        std::cerr << i << " ";
    }
    std::cerr << "\n";

    return 0;
}