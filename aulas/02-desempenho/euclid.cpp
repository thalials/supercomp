#include <iostream>
#include <vector>
#include <cmath>

typedef std::vector<std::vector<double>> matriz;

void calcula_distancias(matriz &mat, std::vector<double> &x, std::vector<double> &y) {
    int n = x.size();
    for (int i = 0; i < n; i++) {
        std::vector<double> linha(n);
        for (int j = 0; j < n; j++) {
            if (j < i) {
                linha[j] = mat[j][i];
            } else {
                double dx = x[i] - x[j];
                double dy = y[i] - y[j];
                linha[j] = sqrt(dx*dx + dy*dy);    
            }
        }
        mat.push_back(linha);
    }

}

int main() {
    matriz mat;
    std::vector<double> x, y;
    int n;

    std::cin >> n;

    for (int i = 0; i < n; i++) {
        double xt, yt;
        std::cin >> xt >> yt;
        x.push_back(xt);
        y.push_back(yt);
    }

    calcula_distancias(mat, x, y);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }


    return 0;
}