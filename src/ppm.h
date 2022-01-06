#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "types.h"
#include "maths_utils.h"

class PPM
{
    public:
        PPM(const char* filepath, const uint32 width, const uint32 height)
        :
            filepath_(filepath),
            width_(width), 
            height_(height)
        {
            std::vector<Color> tmp;

            for (uint32 j = 0; j < height_; ++j)
            {
                for (uint32 i = 0; i < width_; ++i)
                    tmp.push_back(Color(0, 0, 0));

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

        Color get_pixel(uint32 i, uint32 j) const
        {
            return pixels_[j][i];
        }

        void write_pixel(uint32 i, uint32 j, Color pixel)
        {
            pixels_[j][i] = pixel;
        }

        void free()
        {
            for (uint32 j = 0; j < height_; ++j)
                pixels_[j].clear();

            pixels_.clear();
        }

        void save_file()
        {
            std::ofstream file;

            file.open(filepath_);

            file << "P3\n" << width_ << ' ' << height_ << "\n255\n";

            for (uint32 j = 0; j < height_; ++j)
            {
                for (uint32 i = 0; i < width_; ++i)
                {
                    auto pixel = get_pixel(i, height_ - 1 - j);
                    double r = pixel.x();
                    double g = pixel.y();
                    double b = pixel.z();

                    // Write the translated [0, 255] value of each color component.
                    r = static_cast<int>(255 * maths::clamp(r, 0, 1));
                    g = static_cast<int>(255 * maths::clamp(g, 0, 1));
                    b = static_cast<int>(255 * maths::clamp(b, 0, 1));

                    file << r << ' ' << g << ' ' << b << '\n';
                }
            }

            file.close();
        }

    private:
        const char* filepath_;
        const uint32 width_;
        const uint32 height_;
        std::vector<std::vector<Color> > pixels_;
};