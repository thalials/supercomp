#include <iostream>
#include <string>
#include "imagem.hpp"
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/copy.h>
#include <thrust/functional.h>


#include <vector>

struct media {
    int cols;

    media(int cols) : cols(cols) {};

    __host__ __device__
    unsigned char operator() (const unsigned char &el) {
        if (el > 127) return 255;
        return 0;
    }
};

int main(int argc, char *argv[]) {
    Imagem im = Imagem::read(std::string(argv[1]));

    // COPIAR P/ GPU
    thrust::device_vector<unsigned char> pixels_gpu (im.pixels, im.pixels + im.total_size);

    // transform
    media lim(im.cols);
    thrust::transform(pixels_gpu.begin(), pixels_gpu.end(), pixels_gpu.begin(), lim);

    // copia de volta para CPU
    thrust::copy(pixels_gpu.begin(), pixels_gpu.end(), im.pixels);
    

    im.write("out.pgm");
    return 0;
}