#include <thrust/random.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>
#include <vector>

struct rng_gpu {
    thrust::default_random_engine eng;
    thrust::uniform_real_distribution<double> d;

    __device__ __host__
    double operator() (const int &i) {
        return d(eng);
    }
};

int main() {
    thrust::default_random_engine eng(10);
    thrust::uniform_real_distribution<double> d(25, 40);

    for (int i = 0; i < 10; i++) {
        std::cout << d(eng) << "\n";
    }

    rng_gpu rc = {.eng = eng, .d = d};
    
    thrust::device_vector<double> vec(1000);
    thrust::transform(thrust::make_counting_iterator<int>(0),
                      thrust::make_counting_iterator<int>(1000),
                      vec.begin(),
                      rc);

    for (int i = 0; i < 10; i++) {
        std::cout << vec[i] << "\n";
    }

    return 0;
}