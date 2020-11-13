#include <iostream>
#include <vector>
#include <thrust/device_vector.h>
#include <thrust/functional.h>

int main() {
    std::vector<double> stocks_ms, stocks_aapl;
    while (std::cin) {
        double mstf, aapl;
        std::cin >> mstf >> aapl;
        stocks_aapl.push_back(aapl);
        stocks_ms.push_back(mstf);
    };
    std::cerr << stocks_aapl.size() << "\n";

    thrust::device_vector<double> stocks_ms_dev(stocks_ms), stocks_aapl_dev(stocks_aapl);
    thrust::device_vector<double> diff(stocks_aapl.size());

    thrust::transform(stocks_ms_dev.begin(), stocks_ms_dev.end(), stocks_aapl_dev.begin(), diff.begin(), thrust::minus<double>());
    double soma = thrust::reduce(diff.begin(), diff.end());   

    std::cout << (soma / stocks_ms.size()) << "\n";

    return 0;
}