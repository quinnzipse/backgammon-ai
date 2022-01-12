#pragma once

#include <istream>
#include <string>


enum color
{
    none = 0,
    white = 1,
    black = 2
};

color read_color_from_stream(std::istream &input_stream);

int read_next_int_from_stream(std::istream &input_stream);