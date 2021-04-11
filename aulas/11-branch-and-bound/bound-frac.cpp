#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct objeto {
    int id;
    int peso;
    int valor;

    bool operator <(objeto &a) {
        return double(valor)/peso > double(a.valor)/a.peso;
    }
};

struct solucao {
    std::vector<bool> usado;
    int valor;
    int peso;

    solucao(int N) {
        usado.resize(N, false);
        valor = peso = 0;
    }
};

long num_copy = 0, num_leafs = 0, num_bounds = 0;
std::vector<long> bound_level;

void busca_exaustiva(const std::vector<objeto> &obj, int C, 
                    solucao &melhor, 
                    solucao &atual,
                    int limite_superior_valor, int i = 0) {

    if (i == obj.size()) {
        num_leafs++;
        if (atual.valor > melhor.valor) {
            melhor = atual;
            num_copy++;
        }
        return;
    }

    // VALE A PENA CONTINUAR?
    int inclui_todos = atual.valor + limite_superior_valor;
    if (inclui_todos <= melhor.valor) {
        num_bounds++;
        bound_level[i]++;

        return;
    } 

    int idx = obj[i].id;
    if (obj[i].peso <= C) {
        atual.usado[idx] = true;
        atual.valor += obj[i].valor;
        atual.peso += obj[i].peso;

        busca_exaustiva(
            obj, C - obj[i].peso, melhor, atual,
            limite_superior_valor - obj[i].valor, i+1);

        atual.usado[idx] = false;
        atual.valor -= obj[i].valor;
        atual.peso -= obj[i].peso;
    }

    atual.usado[idx] = false;    
    busca_exaustiva(obj, C, melhor, atual, limite_superior_valor - obj[i].valor, i+1);
}

int main() {
    int N, W;
    std::cin >> N >> W;
    std::vector<objeto> objetos(N);
    
    int valor_total = 0;
    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        std::cin >> objetos[i].peso >> objetos[i].valor;
        valor_total += objetos[i].valor;
    }

    std::sort(objetos.begin(), objetos.end());

    bound_level.resize(N, 0);

    solucao melhor(N);
    solucao atual(N);
    busca_exaustiva(objetos, W, melhor, atual, valor_total);

    std::cout << melhor.peso << " " << melhor.valor << " 1\n";
    for (int i = 0; i < N; i++) {
        if (melhor.usado[i]) {
            std::cout << i << " ";
        }
    }

    std::cout << "\n";
    std::cerr << "num copy "<< num_copy << "\n";
    std::cerr << "num leafs "<< num_leafs << "\n";
    std::cerr << "num bounds "<< num_bounds << "\n";

    for (int i = 0; i < N; i++) {
        std::cout << bound_level[i] << " ";
    }
    std::cout << "\n";


    return 0;
}