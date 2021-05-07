#include <vector>
#include <iostream>
#include <unistd.h>


double conta_complexa(int i) {
	sleep(1);
	return 2 * i;
}

int main() {
	int N = 10; 
	double p;
	std::vector<double> vec;
	#pragma omp parallel for 
	for (int i = 0; i < N; i++) {
		p = conta_complexa(i);
		#pragma omp critical
		{
			vec.push_back(p);
		
		}		
	}
	
	for (int i = 0; i < N; i++) {
		std::cout << vec[i] << " ";
	}
	
	return 0;
}
