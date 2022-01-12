#include <iostream>
#include <fstream>

#include "../include/game_state.h"
#include "../include/action.h"

int main()
{
    std::ifstream file_stream("test_input.txt");
    std::istream &input_stream = file_stream;

    std::shared_ptr<game_state> game_state_instance = game_state::generate_from_stream(input_stream);

    std::cout << *game_state_instance;

    // TODO: need to use alpha beta pruning to find the next move.
}

action find_next_move(game_state *game_state_instance)
{
    std::pair<int, action> best_move = find_max_move(game_state_instance, -1000000, 1000000);

    return best_move.second;
}

const std::pair<int, action> find_max_move(game_state *game_state_instance, int alpha, int beta)
{
    // If game is over, return the utility for the current player and null as action.
    if (game_state_instance->is_game_over())
        return std::make_pair(game_state_instance->utility(), action());

    std::pair<int, action> max_value_move = std::make_pair(-1000000, action());

    // Generate all possible moves.
    std::vector<game_state *> *next_possible_states = game_state_instance->generate_possible_next_states();

    // If game is not over, return the max of the min of the next moves.
    // for every possible action, find the min of the next moves.
    for (size_t i = 0; i < next_possible_states->size(); i++)
    {
        // Find the min value of that state.
        std::pair<int, action> min_move = find_min_move(next_possible_states->at(i), alpha, beta);

        // If the min value is greater than the max value, update the max value.
        if (min_move.first > max_value_move.first)
        {
            beta = min_move.first;
            max_value_move.first = min_move.first;
            max_value_move.second = min_move.second;
        }

        // If the min value is more than beta, return immediately.
        if (max_value_move.first >= beta)
            return max_value_move;
    }

    // Return the max value and the action.
}

std::pair<int, action> find_min_move(game_state *game_state_instance, int alpha, int beta)
{
    // If game is over, return the utility for the current player and null as action.

    // If game is not over, return the min of the max of the next moves.
    // for every possible action, find the max of the next moves.
    {
        // Make a modified game state instance.
        // Find the max value of that state.
        // If the max value is less than the min value, update the min value.

        // If the max value is less than alpha, return immediately.
    }

    // Return the max value and the action.
}
