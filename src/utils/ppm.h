#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <glm.hpp>

#include "types.h"
#include "maths.h"

namespace utils
{
    class PPM
    {
        public:
            PPM(const uint32 width, const uint32 height)
            :
                width_(width), 
                height_(height)
            {
                std::vector<glm::vec3> tmp;

                for (uint32 j = 0; j < height_; ++j)
                {
                    for (uint32 i = 0; i < width_; ++i)
                        tmp.push_back(glm::vec3(0));

                    pixels_.push_back(tmp);

                    tmp.clear();
                }
            }

            uint32 height() const
            {
                return height_;
            }

            uint32 width() const
            {
                return width_;
            }

            glm::vec3 get_pixel(uint32 i, uint32 j) const
            {
                return pixels_[j][i];
            }

            void write_pixel(uint32 i, uint32 j, glm::vec3 pixel)
            {
                pixels_[j][i] = pixel;
            }

            void free()
            {
                for (uint32 j = 0; j < height_; ++j)
                    pixels_[j].clear();

                pixels_.clear();
            }

            void save_file(const char* filepath)
            {
                std::ofstream file;

                file.open(filepath);

                file << "P3\n" << width_ << ' ' << height_ << "\n255\n";

                for (uint32 j = 0; j < height_; ++j)
                {
                    for (uint32 i = 0; i < width_; ++i)
                    {
                        auto pixel = get_pixel(i, height_ - 1 - j);
                        float r = pixel.x;
                        float g = pixel.y;
                        float b = pixel.z;

                        // Write the translated [0, 255] value of each color component.
                        r = static_cast<int>(255 * utils::clamp(r, 0, 1));
                        g = static_cast<int>(255 * utils::clamp(g, 0, 1));
                        b = static_cast<int>(255 * utils::clamp(b, 0, 1));

                        file << r << ' ' << g << ' ' << b << '\n';
                    }
                }

                file.close();
            }

        private:
            const uint32 width_;
            const uint32 height_;
            std::vector<std::vector<glm::vec3> > pixels_;
    };
}