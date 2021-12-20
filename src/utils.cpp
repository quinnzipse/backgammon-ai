#include "../include/utils.h"

color read_color_from_stream(std::istream &input_stream)
{
    return read_next_int_from_stream(input_stream) == color::white ? color::white : color::black;
}

int read_next_int_from_stream(std::istream &input_stream)
{
    std::string input;
    input_stream >> input;

    return std::stoi(input);
}