#include "../include/game_state.h"

std::shared_ptr<game_state> game_state::generate_from_stream(std::istream &input_stream)
{
    std::shared_ptr<game_state> game_state_instance = std::make_shared<game_state>();

    game_state_instance->color_of_actor = read_color_from_stream(input_stream);
    game_state_instance->gameboard_instance = gameboard::generate_from_stream(input_stream);
    game_state_instance->die_rolls = dice::generate_from_stream(input_stream);

    return game_state_instance;
}

std::shared_ptr<std::vector<int>> read_die_rolls(std::istream &input_stream)
{
    std::shared_ptr<std::vector<int>> die_rolls = std::make_shared<std::vector<int>>();

    int number_of_dice_rolls = read_next_int_from_stream(input_stream);

    for (int i = 0; i < number_of_dice_rolls; i++)
    {
        int dice_roll = read_next_int_from_stream(input_stream);
        die_rolls->push_back(dice_roll);
    }

    return die_rolls;
}

std::shared_ptr<std::vector<game_state *>> game_state::generate_possible_next_states()
{
    // TODO: This is messed up.
    return std::make_shared<std::vector<game_state *>>();
}

int roll_index = 0;
int checker_index = 0;

std::pair<int, int> next_dice_roll(){ 
    if(roll_index == 36){
        roll_index = 0;
        return std::make_pair<>(0, 0);
    }
    
    std::pair<int, int> dice_rolls;

    dice_rolls.first = (roll_index / 6) + 1;
    dice_rolls.second = (roll_index % 6) + 1;

    roll_index++;

    return dice_rolls;
}

std::pair<int, int> next_checker_move(){
    if(checker_index == 26){
    }


    checker_index++;
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

int game_state::utility()
{
    return 0;
}
