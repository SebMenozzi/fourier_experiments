#pragma once

#include <iostream>
#include <glm.hpp>

#include "maths.h"
#include "types.h"
#include "ppm.h"

namespace utils
{
    inline PPM image_to_ppm(uint8* image, uint32 width, uint32 height, uint32 channels)
    {
        auto ppm = PPM(width, height);

        uint32 size = width * height * channels;
        uint32 i = 0;

        for (uint8 *p = image; p != image + size; p += channels, ++i)
        {
            auto pixel = glm::vec3(
                utils::scale(*p, 0, 255, 0, 1),
                utils::scale(*(p + 1), 0, 255, 0, 1),
                utils::scale(*(p + 2), 0, 255, 0, 1)
            );

            uint32 x = i % width;
            uint32 y = height - 1 - i / width;

            ppm.write_pixel(x, y, pixel);
        }

        return ppm;
    }

    inline uint8* convert_to_gray(uint8* image, uint32 width, uint32 height, uint32 channels)
    {
        size_t size = width * height * channels;

        uint8* gray_image = (uint8*) malloc(size);
        if (gray_image == nullptr)
        {
            std::cerr << "Failure to allocate memory for the gray image!" << std::endl;
            return nullptr;
        }

        for (uint8 *p = image, *pg = gray_image; p != image + size; p += channels, pg += channels)
        {
            float average = (*p + *(p + 1) + *(p + 2)) / 3;
            *pg = (uint8) average;
            *(pg + 1) = (uint8) average;
            *(pg + 2) = (uint8) average;
        }

        return gray_image;
    }

    inline PPM complexes_to_ppm(std::vector<std::vector<complex> > complexes)
    {
        const uint32 width = complexes[0].size();
        const uint32 height = complexes.size();

        auto ppm = utils::PPM(width, height);

        for (uint32 j = 0; j < height; ++j)
        {
            for (uint32 i = 0; i < width; ++i)
            {
                float value = complexes[j][i].real();
                ppm.write_pixel(i, j, glm::vec3(value));
            }
        }

        return ppm;
    }
}