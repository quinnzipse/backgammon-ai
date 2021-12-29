#include "../include/gameboard.h"

gameboard *gameboard::generate_from_stream(std::istream &input_stream)
{
    gameboard *gameboard_instance = new gameboard();

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
        gameboard_instance->points[i] = point::generate_from_stream(input_stream);

    gameboard_instance->white_checkers_on_bar = read_next_int_from_stream(input_stream);
    gameboard_instance->black_checkers_on_bar = read_next_int_from_stream(input_stream);

    return gameboard_instance;
}

gameboard::gameboard() {}

std::ostream &operator<<(std::ostream &output_stream, gameboard &gameboard_instance)
{
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
        output_stream << gameboard_instance.points[i] << " " << std::endl;

    output_stream << "White checkers on bar: " << gameboard_instance.white_checkers_on_bar << std::endl
                  << "Black checkers on bar: " << gameboard_instance.black_checkers_on_bar << std::endl;

    return output_stream;
}