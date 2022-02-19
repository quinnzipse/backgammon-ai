#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

// In the test files the colors (aka actors) are 1 indexed.
const enum ACTOR { WHITE = 0,
                   BLACK = 1 };

const int NUMBER_OF_PLAYERS = 2;
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
    std::vector<int> checkers_on_bar;

    state() = default;

    state(const state &s1)
    {
        board = s1.board;
        dice_rolls = s1.dice_rolls;
        checkers_on_bar = s1.checkers_on_bar;
    }

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

        std::cout << state.checkers_on_bar[ACTOR::WHITE] << std::endl
                  << state.checkers_on_bar[ACTOR::BLACK] << std::endl;

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

        output_state.checkers_on_bar.reserve(NUMBER_OF_PLAYERS);
        output_state.checkers_on_bar.emplace_back(read_next_int_from_stream(input_stream));
        output_state.checkers_on_bar.emplace_back(read_next_int_from_stream(input_stream));

        int number_of_dice_rolls = read_next_int_from_stream(input_stream);

        output_state.dice_rolls.reserve(number_of_dice_rolls);

        for (int i = 0; i < number_of_dice_rolls; i++)
            output_state.dice_rolls.emplace_back(read_next_int_from_stream(input_stream));
    }

    // TODO: Does not recognize the constraints of bearing off.
    bool is_open(const int location, const ACTOR actor) const
    {
        return board[location].first <= 1 || board[location].second == actor;
    }
};

class dice
{
    int dice_index;

public:
    dice() : dice_index(0)
    {
    }

    bool has_next_roll()
    {
        return dice_index != 35;
    }

    std::pair<int, int> next_dice_roll()
    {
        std::pair<int, int> next_roll = std::make_pair<int, int>(0, 0);

        if (dice_index == 35)
        {
            dice_index = 0;
            return next_roll;
        }

        next_roll.first = (dice_index / 6) + 1;
        next_roll.second = (dice_index % 6) + 1;

        dice_index++;

        return next_roll;
    }
};

class moves
{
    int move_index;
    int move_step;
    int spaces_to_move;
    state s;
    ACTOR actor;

public:
    moves(int dice_roll, ACTOR actor, state &s) : move_index(0), move_step(1), spaces_to_move(dice_roll), s(s), actor(actor)
    {
        if (actor == ACTOR::BLACK)
        {
            move_index = NUMBER_OF_POINTS;
            move_step = -1;
        }
    }

    bool has_next_move()
    {
        return 0 <= move_index && move_index <= NUMBER_OF_POINTS;
    }

    std::pair<int, int> next_move()
    {
        std::pair<int, int> next_move = std::make_pair<int, int>(-1, -1);

        // Find the next move.
        while (0 <= move_index && move_index <= NUMBER_OF_POINTS)
        {
            int move_to_index = move_index + (move_step * spaces_to_move);

            if (s.board[move_index].second == actor &&
                s.is_open(move_to_index, actor))
            {
                next_move.first = move_index;
                next_move.second = move_to_index;

                break;
            }

            move_index += move_step;
        }

        move_index += move_step;

        return next_move;
    }
};

int max(state s, int alpha, int beta)
{
    // Actor WHITE will always be moving
    std::cout << s << alpha << beta << std::endl;

    // If game is over, return the utility for the current player and null as action.
    if (s.game_over())
        return s.utility(); // TODO: Might need to multiply this by the depth.

    std::pair<int, action> max_value_move = std::make_pair(-1000000, action());

    // Generate all possible moves.
    // Since the game is not over, return the max of the min of the next moves.
    // for every possible action, find the min of the next moves.
    dice d = dice();
    while (d.has_next_roll())
    {
        std::pair<int, int> roll = d.next_dice_roll();

        moves m = moves(roll.first, ACTOR::WHITE, s);

        while (m.has_next_move())
        {
            std::pair<int, int> move = m.next_move();
            if (move.first == -1)
                continue;

            // Update state

            // TODO: Use updated state
            moves m2 = moves(roll.second, ACTOR::WHITE, s);
            while (m2.has_next_move())
            {
                std::pair<int, int> move2 = m2.next_move();
                if (move2.first == -1)
                    continue;

                // Update state

                // Find the min value of that state.
                // If the min value is greater than the max value, update the max value.
                // If the min value is more than beta, return immediately.
            }
        }

        // Can add a check to see if roll.first == roll.second (Swapping order wouldn't matter)

        moves m = moves(roll.second, ACTOR::WHITE, s);
        while (m.has_next_move())
        {
            std::pair<int, int> move = m.next_move();
            if (move.first == -1)
                break;

            // Update state

            // TODO: Use updated state
            moves m2 = moves(roll.first, ACTOR::WHITE, s);
            while (m2.has_next_move())
            {
                std::pair<int, int> move2 = m2.next_move();
                if (move2.first == -1)
                    break;

                // Update state

                // Find the min value of that state.
                // If the min value is greater than the max value, update the max value.
                // If the min value is more than beta, return immediately.
            }
        }
    }

    // Return the max value and the action.
    return -1;
}

int min(state s, int alpha, int beta)
{
    // Actor BLACK will always be moving
    std::cout << s << alpha << beta << std::endl;

    // If game is over, return the utility for the current player and null as action.
    if (s.game_over())
        return s.utility(); // TODO: Might need to multiply this by the depth.

    std::pair<int, action> min_value_move = std::make_pair(1000000, action());

    // Since the game is not over, return the min of the max of the next moves.
    // for every possible action, find the max of the next moves.
    dice d = dice();
    while (d.has_next_roll())
    {
        std::pair<int, int> roll = d.next_dice_roll();

        moves m = moves(roll.first, ACTOR::BLACK, s);

        while (m.has_next_move())
        {
            std::pair<int, int> move = m.next_move();
            if (move.first == -1)
                continue;

            // Update state

            // TODO: Use updated state
            moves m2 = moves(roll.second, ACTOR::BLACK, s);
            while (m2.has_next_move())
            {
                std::pair<int, int> move2 = m2.next_move();
                if (move2.first == -1)
                    continue;

                // Make a modified game state instance.
                // Find the max value of that state.
                // If the max value is less than the min value, update the min value.

                // If the max value is less than alpha, return immediately.
            }
        }

        // Can add a check to see if roll.first == roll.second (Swapping order wouldn't matter)

        moves m = moves(roll.second, ACTOR::BLACK, s);
        while (m.has_next_move())
        {
            std::pair<int, int> move = m.next_move();
            if (move.first == -1)
                break;

            // Update state

            // TODO: Use updated state
            moves m2 = moves(roll.first, ACTOR::BLACK, s);
            while (m2.has_next_move())
            {
                std::pair<int, int> move2 = m2.next_move();
                if (move2.first == -1)
                    break;

                // Update state

                // Find the min value of that state.
                // If the min value is greater than the max value, update the max value.
                // If the min value is more than beta, return immediately.
            }
        }
    }

    // Return the min value and the action.
    return -1;
}

int main()
{
    std::ifstream input_stream("test_input_1.txt");

    // Read in an input file
    int color_of_actor = read_next_int_from_stream(input_stream);

    state game_state;
    state::read_from_stream(input_stream, game_state);

    // Verify by printing it out.
    std::cout << "Read in:" << std::endl
              << color_of_actor << std::endl
              << game_state << std::endl;

    int utility;

    if (color_of_actor == 1)
        utility = max(game_state, -100000, 100000);
    else
        utility = min(game_state, -100000, 100000);

    std::cout << "Best Outcome: " << utility << std::endl;
}