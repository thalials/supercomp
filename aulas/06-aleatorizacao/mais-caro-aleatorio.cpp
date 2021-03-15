#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct objeto {
    int peso, valor, id;

    bool operator <(objeto &a) {
        return valor > a.valor;
    }
};

int main () {
    int N, peso_maximo;
    std::cin >> N >> peso_maximo;
    std::vector<objeto> objetos(N);
    std::vector<bool> usados(N, false);

    int seed = 10;
    char *SEED_VAR = getenv("SEED");
    if (SEED_VAR != NULL) {
        seed = atoi(SEED_VAR);
    }
    
    std::default_random_engine eng(seed);
    std::uniform_real_distribution<double> dist;
    

    for (int i = 0; i < N; i++) {
        objetos[i].id = i;
        std::cin >> objetos[i].peso >> objetos[i].valor;
    }

    std::sort(objetos.begin(), objetos.end());

    int peso_atual = 0;
    int valor_atual = 0;
    for (auto &obj : objetos) {
        double rnd_num = dist(eng);
        std::cerr << rnd_num << "\n";
        if (peso_atual + obj.peso <= peso_maximo &&
            rnd_num <= 0.5) {
            peso_atual += obj.peso;
            valor_atual += obj.valor;
            usados[obj.id] = true;
        } else if (rnd_num > 0.75) {
            // SELECIONAR OUTRO PARA TENTAR
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