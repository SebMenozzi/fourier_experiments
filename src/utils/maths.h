#pragma once

#include <iostream>
#include <cmath>

namespace utils
{
    // MARK: - Random
    
    inline float random()
    {
        return rand() / (RAND_MAX + 1.0);
    }

    inline float random(float min, float max)
    {
        return min + (max - min) * random();
    }

    inline int random(int min, int max)
    {
        return static_cast<int>(random((float) min, (float) max + 1));
    }

    // MARK: - Clamp, Lerp, Scale

    inline float clamp(float value, float min, float max)
    {
        return std::fmax(min, std::fmin(max, value));
    }

    inline float lerp(float t, float a, float b)
    {
        return a + t * (b - a);
    }

    inline float scale(float value, float oldMin, float oldMax, float newMin, float newMax)
    {
        return (
            (newMax - newMin) *
            ((value - oldMin) / (oldMax - oldMin)) + 
            newMin
        );
    }
}