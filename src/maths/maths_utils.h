#pragma once

#include <iostream>
#include <cstdlib>
#include <cmath>

namespace maths
{
    inline double degrees_to_radians(double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    inline double random_double()
    {
        return rand() / (RAND_MAX + 1.0);
    }

    inline double random_double(double min, double max)
    {
        return min + (max - min) * random_double();
    }

    inline int random_int(int min, int max)
    {
        return static_cast<int>(random_double(min, max + 1));
    }

    inline double clamp(double x, double min, double max)
    {
        if (x < min) return min;
        if (x > max) return max;

        return x;
    }
}