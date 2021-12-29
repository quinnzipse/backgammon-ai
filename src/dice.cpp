#include "../include/dice.h"

// TODO: This is misleading. The dice class should be renamed to moves because it is not representing dice but the moves that the dice rolls indicate.

dice *dice::generate_from_stream(std::istream &stream)
{
    dice *dice_instance = new dice();

    int number_of_dice_rolls = read_next_int_from_stream(stream);

    for (int i = 0; i < number_of_dice_rolls; i++)
    {
        int dice_roll = read_next_int_from_stream(stream);
        dice_instance->die_rolls.push_back(dice_roll);
    }

    return dice_instance;
}

std::ostream &operator<<(std::ostream &output_stream, dice &dice_instance)
{
    output_stream << "There are " << dice_instance.die_rolls.size() << " dice rolls -> ";

    for (size_t i = 0; i < dice_instance.die_rolls.size(); i++)
    {
        output_stream << dice_instance.die_rolls[i];
        if (i != dice_instance.die_rolls.size() - 1)
            output_stream << ", ";
    }

    return output_stream;
}