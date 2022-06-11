#include <random>
#include <iostream>
using namespace std;

int main(){
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);

    default_random_engine generator1;
    uniform_int_distribution<int> distribution1(-2,5);
    distribution1(generator1); // gera número

    cout << distribution(generator) << endl;
    cout << distribution1(generator1) << endl;
}