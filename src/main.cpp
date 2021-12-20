#include <iostream>
#include <fstream>

#include "../include/facts.h"
#include "../include/utils.h"
#include "../include/gameboard.h"

int main()
{
    std::string input;

    color color_of_actor = read_color_from_stream(std::cin);

    std::cout << "color_of_actor: " << (color_of_actor == color::white ? "White" : "Black") << std::endl
              << std::endl;

    gameboard *gameboard_instance = gameboard::generate_from_stream(std::cin);

    std::cout << "gameboard_instance: " << std::endl
              << *gameboard_instance << std::endl;

    int number_of_white_checkers_on_bar = read_next_int_from_stream(std::cin);
    int number_of_black_checkers_on_bar = read_next_int_from_stream(std::cin);

    std::cout << "number_of_white_checkers_on_bar: " << number_of_white_checkers_on_bar << std::endl
              << "number_of_black_checkers_on_bar: " << number_of_black_checkers_on_bar << std::endl
              << std::endl;

    int number_of_dice_rolls = read_next_int_from_stream(std::cin);

    std::cout << "number_of_dice_rolls: " << number_of_dice_rolls << std::endl;

    for (int i = 0; i < number_of_dice_rolls; i++)
    {
        int dice_roll = read_next_int_from_stream(std::cin);

        std::cout << "dice_roll: " << dice_roll << std::endl;
    }

    // TODO: need to use alpha beta pruning to find the next move.

}