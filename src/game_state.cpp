#include "../include/game_state.h"

game_state *game_state::generate_from_stream(std::istream &input_stream)
{
    color color_of_actor = read_color_from_stream(input_stream);
    gameboard *gameboard_instance = gameboard::generate_from_stream(input_stream);

    // TODO: This should be a part of the gameboard class.
    int number_of_white_checkers_on_bar = read_next_int_from_stream(input_stream);
    int number_of_black_checkers_on_bar = read_next_int_from_stream(input_stream);

    int number_of_dice_rolls = read_next_int_from_stream(std::cin);

    for (int i = 0; i < number_of_dice_rolls; i++)
        int dice_roll = read_next_int_from_stream(std::cin);
}

std::vector<int> *read_die_rolls(std::istream &input_stream)
{
    std::vector<int> *die_rolls = new std::vector<int>();

    int number_of_dice_rolls = read_next_int_from_stream(input_stream);

    for (int i = 0; i < number_of_dice_rolls; i++)
    {
        int dice_roll = read_next_int_from_stream(input_stream);
        die_rolls->push_back(dice_roll);
    }

    return die_rolls;
}