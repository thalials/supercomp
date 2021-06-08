#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>
#include <vector>

struct rng_transform {
    int SEED;

    __device__ __host__
    double operator()(const int &i) { 
        thrust::default_random_engine eng(i * SEED);
        thrust::uniform_real_distribution<double> d(25, 40);

        eng.discard(1000);
        
        return d(eng);
    }
};

int main() {
    thrust::default_random_engine eng(10);
    thrust::uniform_real_distribution<double> d(25, 40);

    for (int i = 0; i < 10; i++) {
        std::cout << d(eng) << "\n";
    }

    rng_transform rt = {.SEED = 10};

    thrust::device_vector<double> vec(10);

    thrust::transform(thrust::make_counting_iterator<int>(0),
                      thrust::make_counting_iterator<int>(10),
                      vec.begin(),
                      rt);

    for (int i = 0; i < 10; i++) {
        std::cout << vec[i] << "\n";
    }

    return 0;
}