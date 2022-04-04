#include <iostream>
#include <iomanip>  
#include <math.h>
#include <vector>
#include <time.h>
using namespace std;

// g++ -Wall -O3 tarefa1.cpp -o tarefa1

int main() {
    int n;
    double x, y;
    vector<double> vectorX, vectorY;

    cin >> n;
    clock_t startIN = clock();

    for (int i=0; i < n; i++) {
        cin >> x >> y; 
        vectorX.push_back(x);
        //cout << "x: " << x << endl;

        vectorY.push_back(y);
        //cout << "y: " << y << endl;
    }

    clock_t endIN = clock();
    double diff = (double)(endIN - startIN)/CLOCKS_PER_SEC;
    cout << "in:" << diff << endl;

    // matriz D
    vector<vector<double>> D;
    double deltaX, deltaY; 
    
    // inicia a matriz D com zeros
    D.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        D[i].resize(n + 1);
    }

    clock_t startOUT = clock();
    for (int i=0; i < n; i++) {
        for(int j=0; j < n; j++) {
            deltaX = vectorX[i] - vectorX[j];
            deltaY = vectorY[i] - vectorY[j];
            double d = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
            D[i][j] = d;
        }
    }
    clock_t endOUT = clock();
    
    diff = (double)(endOUT - startOUT)/CLOCKS_PER_SEC;
    cout << "out: " << diff << endl;

    // for (int i=0; i < n; i++) {
    //     for (int j=0; j< n; j++) {
    //         cout << setprecision(6) << D[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}