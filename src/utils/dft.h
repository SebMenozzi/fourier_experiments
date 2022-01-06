#pragma once

#include <iostream>
#include <vector>
#include <complex>

#include "types.h"

namespace utils
{
    inline std::vector<complex> DFT1D(const std::vector<complex>& input) 
    {
        std::vector<complex> output;

        for (uint32 k = 0; k < input.size(); ++k)
        {
            auto tmp = complex(0, 0);
            for (uint32 i = 0; i < input.size(); ++i)
            {
                float w = 2 * M_PI * i * k / input.size(); 
                tmp += input[i] * complex(cos(w), -sin(w));
            }

            output.push_back(tmp);
        }

        return output;
    }

    inline std::vector<complex> IDFT1D(const std::vector<complex>& input) 
    {
        std::vector<complex> output;

        for (uint32 i = 0; i < input.size(); ++i)
        {
            auto tmp = complex(0, 0);
            for (uint32 k = 0; k < input.size(); ++k)
            {
                float w = 2 * M_PI * i * k / input.size(); 
                tmp += input[k] * complex(cos(w), sin(w));
            }
            tmp /= input.size();

            output.push_back(tmp);
        }

        return output;
    }

    inline std::vector<std::vector<complex> > transpose(const std::vector<std::vector<complex> > input) {
        auto output = std::vector<std::vector<complex> >(input[0].size(), std::vector<complex>(input.size()));

        for (uint32 i = 0; i < input[0].size(); i++) 
            for (uint32 j = 0; j < input.size(); j++)
                output[i][j] = input[j][i];
        
        return output;
    }

    inline std::vector<std::vector<complex> > DFT2D(
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
}