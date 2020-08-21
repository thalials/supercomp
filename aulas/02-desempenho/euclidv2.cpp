#include <iostream>
#include <vector>
#include <cmath>

typedef std::vector<double> matriz;

#define acesso(m, i, j, w) m[i * w + j]

void calcula_distancias(matriz &mat, std::vector<double> &x, std::vector<double> &y) {
    int n = x.size();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            acesso(mat, i, j, n) = sqrt(dx*dx + dy*dy);
            acesso(mat, j, i, n) = acesso(mat, i, j, n);
        }
    }

}

int main() {
    matriz mat;
    std::vector<double> x, y;
    int n;

    std::cin >> n;
    mat.resize(n * n);
    std::cerr << mat.size() << "\n";

    for (int i = 0; i < n; i++) {
        double xt, yt;
        std::cin >> xt >> yt;
        x.push_back(xt);
        y.push_back(yt);
    }

    calcula_distancias(mat, x, y);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << acesso(mat, i, j, n) << " ";
        }
        std::cout << "\n";
    }


    return 0;
}