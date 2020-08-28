#include <iostream>
#include <iomanip>
#include <vector>

int main () {
    
    int n;

    std::cin >> n;

    std::vector<double> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
        double d;
        std::cin >> d;
        v.push_back(d);
    }

    double avg = 0;
    for (double el : v) {
        avg += el;
    }
    avg /= n;

    double var = 0;
    for (double el : v) {
        var += (el - avg) * (el - avg);
    }
    var /= n;

    std::cout << std::setprecision(2);
    std::cout << avg << " " << var << "\n";

    return 0;
 }