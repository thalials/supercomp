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
    std::vector<int> resposta;
    int valor;
    int peso;

    solucao(int N) {
        usado.resize(N, false);
        resposta.reserve(N);
        valor = peso = 0;
    }

    void add_objeto(objeto &o) {
        resposta.push_back(o.id);
        usado[o.id] = true;
        peso += o.peso;
        valor += o.valor;
    }

    void tira_objeto(objeto &o) {
        // std::cerr << o.id << " - " << usado[o.id] << " ---";
        auto iter = std::find(resposta.begin(), resposta.end(), o.id);
        if (iter == resposta.end()) std::cerr << "NAO ACHOU!!!!!\n\n\n";
        resposta.erase(iter);
        peso -= o.peso;
        valor -= o.valor;
        usado[o.id] = false;
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

    std::default_random_engine eng(10);
    std::uniform_real_distribution<double> aleatorio(0, 1); 

    solucao melhor(N);
    for (int k = 0; k < 1; k++) {
        solucao rand(N);
        for (auto &o : objetos) {
            if (aleatorio(eng) < 0.5) {
                if (o.peso + rand.peso < W) {
                    rand.add_objeto(o);
                }
            }
        }
        std::cerr << "Aleatório: " << rand.valor << "\n";
        bool melhor_local = false;

        while (!melhor_local) {
            melhor_local = true;
            for (objeto &o : objetos) {
                if (rand.usado[o.id]) continue;
                if (o.peso + rand.peso < W) {
                    rand.add_objeto(o);
                    std::cerr << "cheia:" << rand.valor << "\n";
                    melhor_local = false;
                }
            }   

            for (int i = 0; i < N && melhor_local == true; i++) {
                if (rand.usado[i] == false) continue;
                for (int j = i+1; j < N && melhor_local == true; j++) {
                    if (rand.usado[j]) continue;
                    // tenta trocar objeto i (selecionado) por j (fora)
                    int valor_com_troca = rand.valor - objetos[i].valor + objetos[j].valor;
                    int peso_com_troca = rand.peso - objetos[i].peso + objetos[j].peso;
                    if (peso_com_troca < W && valor_com_troca > rand.peso) {
                        rand.tira_objeto(objetos[i]);
                        rand.add_objeto(objetos[j]);
                        std::cerr << "troca:" << rand.valor << "\n";
                        melhor_local = false;
                        break;
                    }
                }
            } 
        }
        std::cerr << "Busca local: " << rand.valor << "\n";

        if (rand.valor > melhor.valor) {
            melhor = rand;
        }
    }
    

    std::cout << melhor.peso << " " << melhor.valor << " 0\n";
    for (int id : melhor.resposta) {
        std::cout << id << " ";
    }
    std::cout << "\n";

    return 0;
}