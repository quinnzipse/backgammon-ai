#include <iostream>
#include <fstream>

#include "../include/game_state.h"

int main()
{
    std::istream *input_stream = new std::ifstream("test_input.txt");

    game_state *game_state_instance = game_state::generate_from_stream(*input_stream);

    std::cout << *game_state_instance;

    // TODO: need to use alpha beta pruning to find the next move.
}