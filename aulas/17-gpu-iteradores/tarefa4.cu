#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/count.h>
#include <thrust/system/omp/execution_policy.h>
#include <thrust/fill.h>
#include <thrust/iterator/constant_iterator.h>

using namespace std;
 
struct is_positive
{
    __host__ __device__
    bool operator()(const double &x)
    {
      return x > 0;
    }
};

int main () {
    thrust::host_vector<double> stocks; // alocado na CPU
    std::ifstream file("stocks.txt");
    for (std::string line; std::getline(file, line); ) {
        stocks.push_back(std::stof(line));
    }
		
	thrust::host_vector<double> ganho_diario(stocks.size()-1);
	thrust::transform(thrust::host, stocks.begin()+1, stocks.end(), stocks.begin(), ganho_diario.begin(), thrust::minus<double>());

	cout << "Ganho diário: ";
    for (const auto& elem : ganho_diario)
        cout << elem << ", ";
    cout << endl;
	int subiu = thrust::count_if(ganho_diario.begin(), ganho_diario.end(), is_positive());

	cout << "Quantas vezes subiu: " << subiu << endl;

}
