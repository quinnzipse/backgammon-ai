#include "../include/gameboard.h"

gameboard *gameboard::generate_from_stream(std::istream &input_stream)
{
    gameboard *gameboard_instance = new gameboard();

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
        gameboard_instance->points[i] = point::generate_from_stream(input_stream);

    return gameboard_instance;
}

gameboard::gameboard() {}

std::ostream &operator<<(std::ostream &output_stream, gameboard &gameboard_instance)
{
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
        output_stream << gameboard_instance.points[i] << " " << std::endl;

    return output_stream;
}