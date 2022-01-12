#include "../include/gameboard.h"

gameboard::gameboard(std::vector<point> &points, int white_checkers_on_bar, int black_checkers_on_bar)
    : points(points), white_checkers_on_bar(white_checkers_on_bar), black_checkers_on_bar(black_checkers_on_bar)
{
}

gameboard *gameboard::generate_from_stream(std::istream &input_stream)
{
    std::vector<point> points;
    points.reserve(NUMBER_OF_POINTS);

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
        points[i].fill_from_stream(input_stream);

    int white_checkers_on_bar = read_next_int_from_stream(input_stream);
    int black_checkers_on_bar = read_next_int_from_stream(input_stream);

    return new gameboard(points, white_checkers_on_bar, black_checkers_on_bar);
}

bool gameboard::is_game_over()
{
    return white_checkers_on_bar >= NUMBER_OF_COLOR_CHECKERS || black_checkers_on_bar >= NUMBER_OF_COLOR_CHECKERS;
}

std::ostream &operator<<(std::ostream &output_stream, gameboard &gameboard_instance)
{
    for (int i = 0; i < NUMBER_OF_POINTS; i++)
        output_stream << gameboard_instance.points[i] << " " << std::endl;

    output_stream << "White checkers on bar: " << gameboard_instance.white_checkers_on_bar << std::endl
                  << "Black checkers on bar: " << gameboard_instance.black_checkers_on_bar << std::endl;

    return output_stream;
}