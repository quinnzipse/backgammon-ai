#include "../include/gameboard.h"

gameboard::gameboard(std::shared_ptr<std::vector<point>> points, int white_checkers_on_bar, int black_checkers_on_bar)
    : points(points), white_checkers_on_bar(white_checkers_on_bar), black_checkers_on_bar(black_checkers_on_bar)
{
}

std::shared_ptr<std::vector<gameboard *>> gameboard::generate_possible_next_states()
{
    // TODO: This is probably pointless
    return std::make_shared<std::vector<gameboard *>>();
}

std::shared_ptr<gameboard> gameboard::generate_from_stream(std::istream &input_stream)
{
    std::shared_ptr<std::vector<point>> points = std::make_shared<std::vector<point>>();
    points->reserve(NUMBER_OF_POINTS);
    points->resize(NUMBER_OF_POINTS);

    for (size_t i = 0; i < NUMBER_OF_POINTS; i++)
        points->at(i).fill_from_stream(input_stream);

    int white_checkers_on_bar = read_next_int_from_stream(input_stream);
    int black_checkers_on_bar = read_next_int_from_stream(input_stream);

    return std::make_shared<gameboard>(points, white_checkers_on_bar, black_checkers_on_bar);
}

bool gameboard::is_game_over()
{
    return white_checkers_on_bar >= NUMBER_OF_COLOR_CHECKERS || black_checkers_on_bar >= NUMBER_OF_COLOR_CHECKERS;
}

std::ostream &operator<<(std::ostream &output_stream, gameboard &gameboard_instance)
{
    for (size_t i = 0; i < NUMBER_OF_POINTS; i++)
        output_stream << gameboard_instance.points->at(i) << " " << std::endl;

    output_stream << "White checkers on bar: " << gameboard_instance.white_checkers_on_bar << std::endl
                  << "Black checkers on bar: " << gameboard_instance.black_checkers_on_bar << std::endl;

    return output_stream;
}