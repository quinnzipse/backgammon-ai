#include "../include/game_state.h"

game_state *game_state::generate_from_stream(std::istream &input_stream)
{
    game_state *game_state_instance = new game_state();

    game_state_instance->color_of_actor = read_color_from_stream(input_stream);
    game_state_instance->gameboard_instance = gameboard::generate_from_stream(input_stream);
    game_state_instance->die_rolls = dice::generate_from_stream(input_stream);

    return game_state_instance;
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

std::vector<game_state *> *game_state::generate_possible_next_states()
{
    return this->gameboard_instance->generate_possible_next_states();
}

bool game_state::is_game_over()
{
    return gameboard_instance->is_game_over();
}

std::ostream &operator<<(std::ostream &output_stream, game_state &game_state_instance)
{
    return output_stream << std::endl
                         << (game_state_instance.color_of_actor == 1 ? "White" : "Black") << " is next to move." << std::endl
                         << *game_state_instance.gameboard_instance << std::endl
                         << *game_state_instance.die_rolls << std::endl;
}