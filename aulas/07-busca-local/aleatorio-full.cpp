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

    int valor_melhor = 0, peso_melhor = 0;
    std::vector<bool> usados_melhor(N, false);

    for (int k = 0; k < 10; k++) {
        int peso_atual = 0;
        int valor_atual = 0;
        std::vector<bool> usados(N, false);

        for (auto &obj : objetos) {
            double rnd_num = dist(eng);
            // std::cerr << rnd_num << "\n";
            if (peso_atual + obj.peso <= peso_maximo &&
                rnd_num <= 0.5) {
                peso_atual += obj.peso;
                valor_atual += obj.valor;
                usados[obj.id] = true;
            }
        }

        for (auto &obj : objetos) {
            double rnd_num = dist(eng);
            // std::cerr << rnd_num << "\n";
            if (peso_atual + obj.peso <= peso_maximo &&
                !usados[obj.id]) {
                peso_atual += obj.peso;
                valor_atual += obj.valor;
                usados[obj.id] = true;
            }
        }

        if (valor_atual > valor_melhor) {
            valor_melhor = valor_atual;
            peso_melhor = peso_atual;
            usados_melhor = usados;
        }
    }
    
    
    std::cout << peso_melhor << " " << valor_melhor << "\n";
    for (int i = 0; i < N; i++) {
        if (usados_melhor[i]) 
            std::cout << i << " ";
    }
    std::cout << "\n";

    return 0;
}