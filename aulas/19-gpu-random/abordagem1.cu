#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/random.h>
#include <thrust/iterator/counting_iterator.h>

struct randgpu {
    __host__ __device__
    double operator()(const int &i) {
        thrust::default_random_engine eng;
        // eng.discard(i);
        thrust::uniform_real_distribution<double> d(25, 40);

        return d(eng);
    }
};

int main() {
    int N = 10;
    thrust::device_vector<double> rng(N);
    randgpu r;
    thrust::transform(thrust::counting_iterator<int>(0), 
                        thrust::counting_iterator<int>(N),
                        rng.begin(),
                        r);
    
    for (auto el : rng) {
        std::cout << el << " ";
    }
    std::cout << "\n";
    return 0;
}