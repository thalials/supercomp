#include "imagem.hpp"
#include <iostream>
#include <random>
#include <omp.h>

int main(int argc, char *argv[]) {
    // Imagem input = Imagem::read(std::string(argv[1]));
    // Imagem output(input.rows, input.cols);

    // auto vec = new std::default_random_engine[omp_get_max_threads()];
    // std::uniform_int_distribution<int> gen(1, 11);

    // #pragma omp parallel for schedule(static)
    // for (int k = 0; k < input.total_size; k++) {
    //     int r = gen(vec[omp_get_thread_num()]);
    //     if (r == 1) {
    //         input.pixels[k] = 0;
    //     } else if (r == 10) {
    //         input.pixels[k] = 255;
    //     }
    // }

    // // adicionar ruido aqui
    // input.write(std::string(argv[2]));
    
    #pragma omp parallel 
    {
        double local = 0;
        #pragma omp for
        for (int i = 0; i < 16; i++) {
            local += i;
        }
        #pragma omp critical
        std::cout << local << "\n";
    }
    
    return 0;

}