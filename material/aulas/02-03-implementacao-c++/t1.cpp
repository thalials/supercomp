#include <iostream>
using namespace std;
#include <math.h>

// g++ -Wall -O3 tarefa1.cpp -o tarefa1

int main()
{
    int n;
    float S = 0.0;

    cin >> n; 

    for (int i=0; i <= n; i++) {
        S += (1/pow(2, i));
    }

    cout << "Soma = " << S << endl;

    return 0;
}