#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <cstdlib>
#include <omp.h>

bool DEBUG=false;

struct input {
    int N;
    std::vector<double> distances;
};

struct solucao {
    std::vector<bool> visitados;
    std::vector<int> ordem;
    double tour;

    solucao(int N) {
        visitados.resize(N, false);
        ordem.resize(N, -1);
        ordem[0] = 0;
        visitados[0] = true;
        tour = INFINITY;
    }

};

#define acesso(m, i, j, w) m[i * w + j]

void calcula_distancias(input &inp, std::vector<double> &x, std::vector<double> &y) {
    int n = x.size();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            acesso(inp.distances, i, j, n) = sqrt(dx*dx + dy*dy);
            acesso(inp.distances, j, i, n) = acesso(inp.distances, i, j, n);
        }
    }
}



int main () {
    input inp;
    std::cin >> inp.N;
    inp.distances.resize(inp.N*inp.N);
    std::vector<double> x(inp.N), y(inp.N);
    for (int i = 0; i < inp.N; i++) {
        std::cin >> x[i] >> y[i];
    }

    calcula_distancias(inp, x, y);

    solucao melhor(inp.N);

    int SEED = 10;
    char *envvar = getenv("SEED");
    if (envvar != NULL) {
        SEED = atoi(envvar);
    }

    char *debug_env = getenv("DEBUG");
    if (debug_env != NULL) {
        int debug_val = atoi(debug_env);
        DEBUG = debug_val == 1;
    }


    #pragma omp parallel for
    for (int k = 0; k < 10 * inp.N; k++) {
        std::default_random_engine eng(SEED * k * 1337);

        solucao s(inp.N);
        for (int i = 0; i < inp.N; i++) {
            s.ordem[i] = i;
            s.visitados[i] = true;
        }

        s.tour = 0;
        for (int i = 0; i < inp.N; i++) {
            std::uniform_int_distribution<int> d(i, inp.N-1);
            int dest = d(eng);
            std::swap(s.ordem[i], s.ordem[dest]);
            if (i > 0) {
                s.tour += acesso(inp.distances, s.ordem[i-1], s.ordem[i], inp.N);
            }
        }
        s.tour += acesso(inp.distances, s.ordem[inp.N-1], s.ordem[0], inp.N);

        bool melhorou = false;
        do {
            melhorou = false;
            for (int i = 0; i < inp.N && !melhorou; i++) {
                for (int j = i+1; j < inp.N && !melhorou; j++) {
                    // std::swap(s.ordem[i], s.ordem[j]);
                    // double new_tour = 0.0;
                    // for (int l = 0; l < inp.N-1; l++) {
                    //     new_tour += acesso(inp.distances, s.ordem[l], s.ordem[l+1], inp.N);
                    // }
                    // new_tour += acesso(inp.distances, s.ordem[0], s.ordem[inp.N-1], inp.N);
                                       
                    double new_tour = s.tour;

                    int b4i = (i - 1 + inp.N) % inp.N;
                    int afteri = (i + 1) % inp.N;
                    int b4j = (j - 1 + inp.N) % inp.N;
                    int afterj = (j + 1) % inp.N;

                    if (afterj != i) {
                        new_tour -= acesso(inp.distances, s.ordem[b4i], s.ordem[i], inp.N);
                        new_tour -= acesso(inp.distances, s.ordem[j], s.ordem[afterj], inp.N);
                    }
                    if (afteri != j) {
                        new_tour -= acesso(inp.distances, s.ordem[i], s.ordem[afteri], inp.N);
                        new_tour -= acesso(inp.distances, s.ordem[b4j], s.ordem[j], inp.N);
                    }
                    
                    if (afterj != i) {
                        new_tour += acesso(inp.distances, s.ordem[b4i], s.ordem[j], inp.N);
                        new_tour += acesso(inp.distances, s.ordem[i], s.ordem[afterj], inp.N);
                    }
                    if (afteri != j) {
                        new_tour += acesso(inp.distances, s.ordem[b4j], s.ordem[i], inp.N);
                        new_tour += acesso(inp.distances, s.ordem[j], s.ordem[afteri], inp.N);
                    }

                    if (new_tour < s.tour) {
                        s.tour = new_tour;
                        melhorou = true;
                        std::swap(s.ordem[i], s.ordem[j]);
                    } else {
                        // std::swap(s.ordem[i], s.ordem[j]);
                    }
                }
            }
        } while (melhorou);

        if (DEBUG) {
            #pragma omp critical
            {
                std::cerr << "local " << s.tour;
                for (int i = 0; i < inp.N; i++) {
                    std::cerr << " " << s.ordem[i];
                }
                std::cerr << "\n";
            }
        }

        if (s.tour < melhor.tour) {
            #pragma omp critical 
            {
                if (s.tour < melhor.tour) {
                    melhor = s;
                }
            }
            
        }
    }

    std::cout << melhor.tour << " 0\n";
    for (int el : melhor.ordem) {
        std::cout << el << " ";
    }
    std::cout << "\n";

    return 0;
}