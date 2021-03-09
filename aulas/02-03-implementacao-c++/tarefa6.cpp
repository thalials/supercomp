#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

void calcula_distancias(const std::vector<double> &x, const std::vector<double> &y, std::vector<double> &mat) {
    int N = x.size();
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            double dist = sqrt(dx*dx + dy*dy);
            mat[j * N + i] = mat[i * N + j] = dist;

        }
    }
}

int main(int argc, char const *argv[])
{
    int N;
    std::cin >> N;
    std::vector<double> x(N), y(N);
    for(int i = 0; i < N; i++) {
        std::cin >> x[i] >> y[i];
    }

    std::vector<double> mat(N*N, 0);
    calcula_distancias(x, y, mat);

    std::cout << std::setprecision(2) << std::fixed;
    // for(const auto &el : mat) {
    //         std::cout << el << " ";
    //     }
    //     std::cout << "\n";
    // }


    return 0;
}
