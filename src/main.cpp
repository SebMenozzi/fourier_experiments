#include <iostream>
#include <vector>
#include <complex>
#include <random>

#include "types.h"
#include "ppm.h"

std::vector<complex> DFT1D(const std::vector<complex>& input) 
{
    std::vector<complex> output;

    for (uint32 k = 0; k < input.size(); ++k)
    {
        auto tmp = complex(0, 0);
        for (uint32 i = 0; i < input.size(); ++i)
        {
            double w = 2 * M_PI * i * k / input.size(); 
            tmp += input[i] * std::complex(cos(w), -sin(w));
        }

        output.push_back(tmp);
    }

    return output;
}

std::vector<complex> IDFT1D(const std::vector<complex>& input) 
{
    std::vector<complex> output;

    for (uint32 i = 0; i < input.size(); ++i)
    {
        auto tmp = complex(0, 0);
        for (uint32 k = 0; k < input.size(); ++k)
        {
            double w = 2 * M_PI * i * k / input.size(); 
            tmp += input[k] * std::complex(cos(w), sin(w));
        }
        tmp /= input.size();

        output.push_back(tmp);
    }

    return output;
}

std::vector<std::vector<complex> > transpose(const std::vector<std::vector<complex> > input) {
    auto output = std::vector<std::vector<complex> >(input[0].size(), std::vector<complex>(input.size()));

    for (uint32 i = 0; i < input[0].size(); i++) 
        for (uint32 j = 0; j < input.size(); j++)
            output[i][j] = input[j][i];
    
    return output;
}

std::vector<std::vector<complex> > DFT2D(
    const std::vector<std::vector<complex> >& input,
    std::vector<complex> (*op)(const std::vector<complex>&)) 
{
    std::vector<std::vector<complex> > output;

    std::vector<std::vector<complex> > output_rows;
    for (uint32 i = 0; i < input.size(); ++i)
        output_rows.push_back(op(input[i]));

    auto output_columns = transpose(output_rows);
    for (uint32 i = 0; i < output_columns.size(); ++i)
        output.push_back(op(output_columns[i]));

    return output;
} 

int main(int argc, char *argv[])
{
    uint32 n = 128;

    // Create random image
    auto image = PPM("image.ppm", n, n);
    for (uint32 j = 0; j < n; ++j)
    {
        for (uint32 i = 0; i < n; ++i)
        {
            double random = maths::random_double(0, 1);
            image.write_pixel(i, j, Color(random));
        }
    }
    image.save_file();

    // Create input to pass in the discret fourier transform
    std::vector<std::vector<complex> > input;
    std::vector<complex> tmp;

    for (uint32 j = 0; j < n; ++j)
    {
        for (uint32 i = 0; i < n; ++i)
        {
            auto pixel = image.get_pixel(i, j);
            double real = (pixel.x() + pixel.y() + pixel.z()) / 3;

            tmp.push_back(complex(real, 0));
        }

        input.push_back(tmp);
        tmp.clear();
    }

    // Create dft image

    auto dft_output = DFT2D(input, DFT1D);

    auto dft_image = PPM("dft.ppm", n, n);
    for (uint32 j = 0; j < n; ++j)
    {
        for (uint32 i = 0; i < n; ++i)
        {
            double value = dft_output[j][i].real();
            dft_image.write_pixel(i, j, Color(value));
        }
    }
    dft_image.save_file();

    // Create iidft image

    auto idft_output = DFT2D(dft_output, IDFT1D);

    auto idft_image = PPM("idft.ppm", n, n);
    for (uint32 j = 0; j < n; ++j)
    {
        for (uint32 i = 0; i < n; ++i)
        {
            double value = idft_output[j][i].real();
            idft_image.write_pixel(i, j, Color(value));
        }
    }
    idft_image.save_file();

    image.free();
    dft_image.free();
    idft_image.free();

    return EXIT_SUCCESS;
}
