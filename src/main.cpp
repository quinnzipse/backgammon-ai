#include <iostream>
#include <fstream>

#include "../include/facts.h"
#include "../include/utils.h"
#include "../include/gameboard.h"

int main()
{
    std::cout << "color_of_actor: " << (color_of_actor == color::white ? "White" : "Black") << std::endl
              << std::endl;

    std::cout << "gameboard_instance: " << std::endl
              << *gameboard_instance << std::endl;

    std::cout << "number_of_white_checkers_on_bar: " << number_of_white_checkers_on_bar << std::endl
              << "number_of_black_checkers_on_bar: " << number_of_black_checkers_on_bar << std::endl
              << std::endl;

    std::cout << "number_of_dice_rolls: " << number_of_dice_rolls << std::endl;

    // TODO: need to use alpha beta pruning to find the next move.
}