#include "../include/point.h"

void point::fill_from_stream(std::istream &input_stream)
{
    this->number_of_checkers = read_next_int_from_stream(input_stream);
    this->color_of_checkers = number_of_checkers == 0 ? color::none : read_color_from_stream(input_stream);
}

bool point::is_open(color color_of_actor)
{
    return number_of_checkers <= 1 || color_of_checkers == color_of_actor;
}

point::point()
    : number_of_checkers(0), color_of_checkers(color::none)
{
}

std::ostream &operator<<(std::ostream &output_stream, point &point_instance)
{
    if (point_instance.number_of_checkers == 0)
        output_stream << "|";

    char checker_symbol = point_instance.color_of_checkers == color::white ? 'O' : 'X';

    for (int i = 0; i < point_instance.number_of_checkers; i++)
        output_stream << checker_symbol;

    return output_stream;
}