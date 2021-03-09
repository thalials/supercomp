#include <iostream>
#include <iomanip>
#include <vector>

int main(int argc, char const *argv[])
{
    int N;
    std::cin >> N;
    std::vector<double> vetor(N);
    for (auto &el : vetor) {
        std::cin >> el;
    }

    double media = 0;
    for (const auto &el : vetor) {
        media += el;
    }
    media /= N;

    double var = 0;
    for (auto el : vetor) {
        var += (el - media) * (el - media);
    }
    var /= N;

    std::cout << std::setprecision(15) << std::fixed;
    std::cout << media << " " << var << "\n";

    return 0;
}
