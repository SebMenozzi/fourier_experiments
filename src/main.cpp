#include <iostream>
#include <vector>
#include <glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "maths.h"
#include "types.h"
#include "ppm.h"
#include "dft.h"
#include "image.h"

int main(int argc, char *argv[])
{
    // Load the image
    int width, height, channels;
    uint8* image = stbi_load("images/lena.jpg", &width, &height, &channels, 3);
    if (image == nullptr)
    {
        std::cerr << "Failure to load the image!" << std::endl;
        return EXIT_FAILURE;
    }
    
    uint8* gray_image = utils::convert_to_gray(image, width, height, channels);
    if (gray_image == nullptr)
    {
        std::cerr << "Failure to create the gray image!" << std::endl;
        return EXIT_FAILURE;
    }
    stbi_write_jpg("build/gray.jpg", width, height, channels, gray_image, 100);

    auto gray_ppm = utils::image_to_ppm(gray_image, width, height, channels);
    gray_ppm.save_file("build/gray.ppm");

     // Create input to pass in the discret fourier transform
    std::vector<std::vector<complex> > input;
    std::vector<complex> tmp;

    for (uint32 j = 0; j < height; ++j)
    {
        for (uint32 i = 0; i < width; ++i)
            tmp.push_back(complex(gray_ppm.get_pixel(i, j).x, 0));

        input.push_back(tmp);
        tmp.clear();
    }

    // Create dft image
    auto dft_output = utils::DFT2D(input, utils::DFT1D);
    auto dft_ppm = utils::complexes_to_ppm(dft_output);
    dft_ppm.save_file("build/dft.ppm");

    // Create iidft image
    auto idft_output = utils::DFT2D(dft_output, utils::IDFT1D);
    auto idft_ppm = utils::complexes_to_ppm(idft_output);
    idft_ppm.save_file("build/idft.ppm");

    gray_ppm.free();
    dft_ppm.free();
    idft_ppm.free();

    return EXIT_SUCCESS;
}
