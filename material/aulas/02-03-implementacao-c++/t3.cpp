#include <iostream>
#include <iomanip>  
#include <math.h>
#include <vector>
using namespace std;

// g++ -Wall -O3 tarefa1.cpp -o tarefa1

int main()
{
    int n;
    float x, mi = 0.0, soma = 0.0;
    vector <float> v;

    cout << "n: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout<< "x: ";

        cin >> x;
        cout << '\n';
        v.push_back(x);
    }

    for (int i = 0; i < int(v.size()); i++) {
        soma += v[i];
    }

    float sigma_2;
    float soma_quadrada = 0.0;
    mi = (1/n) * soma;

    for (int i=0; i < n; i++) {
        soma_quadrada += pow(v[i] - mi, 2);
    }

    sigma_2 = (1/n) * soma_quadrada;


    cout << std::setprecision(15) << sigma_2 << endl;

    return 0;
}