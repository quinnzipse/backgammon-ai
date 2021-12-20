#include <iostream>
#include <fstream>

#include "../include/facts.h"
#include "../include/utils.h"
#include "../include/gameboard.h"

int main()
{
    std::string input;

    color color_of_actor = read_color_from_stream(std::cin);

    std::cout << "color_of_actor: " << color_of_actor << std::endl;

    gameboard *gameboard_instance = gameboard::generate_from_stream(std::cin);

    std::cout << "gameboard_instance: " << std::endl
              << *gameboard_instance << std::endl;
}