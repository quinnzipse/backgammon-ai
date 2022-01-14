#include <iostream>
#include <fstream>
#include <vector>

const int BLACK_BEAR_OFF_INDEX = 0;
const int WHITE_BEAR_OFF_INDEX = 25;
const int NUMBER_OF_POINTS = 26;
const int NUMBER_OF_PLAYER_CHECKERS = 15;

int read_next_int_from_stream(std::istream &input_stream)
{
    std::string input;
    input_stream >> input;

    return std::stoi(input);
}

class action
{
};

class state
{
public:
    std::vector<std::pair<int, int>> board;
    std::vector<int> dice_rolls;
    int white_checkers_on_bar, black_checkers_on_bar;

    state() = default;

    bool game_over() const
    {
        return board[WHITE_BEAR_OFF_INDEX].first == NUMBER_OF_PLAYER_CHECKERS ||
               board[BLACK_BEAR_OFF_INDEX].first == NUMBER_OF_PLAYER_CHECKERS;
    }

    int utility() const
    {
        return board[WHITE_BEAR_OFF_INDEX].first == NUMBER_OF_PLAYER_CHECKERS ? 1 : 0;
    }

    friend std::ostream &operator<<(std::ostream &stream, state &state)
    {
        for (int i = 0; i < NUMBER_OF_POINTS; i++)
        {
            std::pair<int, int> point = state.board[i];
            std::cout << point.first << " " << point.second << std::endl;
        }

        std::cout << state.white_checkers_on_bar << std::endl
                  << state.black_checkers_on_bar << std::endl;

        std::cout << state.dice_rolls.size() << std::endl;

        for (size_t i = 0; i < state.dice_rolls.size(); i++)
            std::cout << state.dice_rolls[i] << std::endl;

        return stream;
    }

    static void read_from_stream(std::ifstream &input_stream, state &output_state)
    {
        output_state.board.reserve(NUMBER_OF_POINTS);

        for (int i = 0; i < NUMBER_OF_POINTS; i++)
        {
            int number_of_checkers = read_next_int_from_stream(input_stream);

            if (number_of_checkers > 0)
            {
                int color = read_next_int_from_stream(input_stream);
                output_state.board.emplace_back(number_of_checkers, color);
            }
            else
            {
                output_state.board.emplace_back(number_of_checkers, 0);
            }
        }

        output_state.white_checkers_on_bar = read_next_int_from_stream(input_stream),
        output_state.black_checkers_on_bar = read_next_int_from_stream(input_stream);

        int number_of_dice_rolls = read_next_int_from_stream(input_stream);

        output_state.dice_rolls.reserve(number_of_dice_rolls);

        for (int i = 0; i < number_of_dice_rolls; i++)
            output_state.dice_rolls.emplace_back(read_next_int_from_stream(input_stream));
    }
};

int main()
{
    std::ifstream input_stream("test_input.txt");

    // Read in an input file
    int color_of_actor = read_next_int_from_stream(input_stream);

    state game_state;
    state::read_from_stream(input_stream, game_state);

    // Verify by printing it out.
    std::cout << "Read in:" << std::endl
              << color_of_actor << std::endl
              << game_state;

    if (color_of_actor == 1)
    {
        // Call max
    }
    else
    {
        // call min
    }
}

int max(state s, int alpha, int beta)
{
    std::cout << s << alpha << beta << std::endl;

    // Actor "1" will always be moving

    // If game is over, return the utility for the current player and null as action.
    if (s.game_over())
        return s.utility(); // TODO: Might need to multiply this by the depth.

    // std::pair<int, action> max_value_move = std::make_pair(-1000000, action());

    // Generate all possible moves.

    // If game is not over, return the max of the min of the next moves.
    // for every possible action, find the min of the next moves.
    {
        // Find the min value of that state.
        // If the min value is greater than the max value, update the max value.
        // If the min value is more than beta, return immediately.
        // Return the max value and the action.
    }

    return -1;
}

int min(state s, int alpha, int beta)
{
    std::cout << s << alpha << beta << std::endl;

    // Actor "2" will always be moving

    // If game is over, return the utility for the current player and null as action.

    // If game is not over, return the min of the max of the next moves.
    // for every possible action, find the max of the next moves.
    {
        // Make a modified game state instance.
        // Find the max value of that state.
        // If the max value is less than the min value, update the min value.

        // If the max value is less than alpha, return immediately.
    }

    // Return the min value and the action.
    return -1;
}