#include <random>
#include <iostream>
#include <omp.h>
#include <vector>

int main() {
    long sum = 0;
    long N = 100000000L;
    /*
    #pragma omp parallel default(none) shared(sum), firstprivate(N)
    {
        int id = omp_get_thread_num();
        int n_threads = omp_get_num_threads();

        std::default_random_engine eng (id * 137321);
        std::uniform_real_distribution<double> dist;

        long chunk_size = N/n_threads;
        long start = id * chunk_size;
        long end = (id + 1) * chunk_size;
        if (end > N) end = N;

        double local_sum = 0;
        for (long i = start; i < end; i++) {
            double x, y;
            x = dist(eng);
            y = dist(eng);
            if (x*x + y*y <= 1) {
                local_sum++;
            }
        }
        #pragma omp critical    
            sum += local_sum;
    }



    #pragma omp parallel default(none) shared(sum), firstprivate(N)
    {
        int id = omp_get_thread_num();
        std::default_random_engine eng (id * 137321);
        std::uniform_real_distribution<double> dist;

        #pragma omp for reduction(+:sum)
        for (long i = 0; i < N; i++) {
            double x, y;
            x = dist(eng);
            y = dist(eng);
            if (x*x + y*y <= 1) {
                sum++;
            }
        }
    }*/

    int n_threads = omp_get_max_threads();
    std::vector<std::default_random_engine> engs(n_threads);
    for (int i = 0; i < n_threads; i++) {
        engs[i] = std::default_random_engine(i * 137321);
    }
    std::vector<std::uniform_real_distribution<double>> dist(n_threads);


    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < N; i++) {
        double x, y;
        int id = omp_get_thread_num();
        x = dist[id](engs[id]);
        y = dist[id](engs[id]);
        if (x*x + y*y <= 1) {
            sum++;
        }
    }
    

    double pi = 4.0 * sum / N;
    std::cout << pi << "\n";
    std::cerr << sum << "\n";

}