#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

// In the test files the colors (aka actors) are 1 indexed.
enum ACTOR
{
    NONE = 0,
    WHITE = 1,
    BLACK = 2
};

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
public:
    std::pair<int, int> first_move;
    std::pair<int, int> second_move;

    action() = default;
    action(const std::pair<int, int> &first_move, const std::pair<int, int> &second_move) : first_move(first_move), second_move(second_move) {}
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

    void update_state(int from, int to)
    {
        int actor = board[from].second;

        // Remove a checker from the designated place.
        assert(board[from].first);

        board[from].first--;

        if (board[from].first == 0)
            board[from].second = ACTOR::NONE;

        // Place the checker in the designated place.
        if (board[to].second != actor)
        {
            if (board[to].first == 0)
            {
                assert(board[to].second == ACTOR::NONE);
                board[to].first++;
            }
            else
            {
                assert(board[to].first == 1);
                checkers_on_bar[(actor == ACTOR::WHITE ? 0 : 1)]++; // move to the bar.
            }

            board[to].second = actor;
        }
        else
        {
            board[to].first++;
        }
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

    bool is_open(const int location, const ACTOR actor) const
    {
        // Check if the location is valid.
        if (location < 0 || location >= NUMBER_OF_POINTS)
            return false;

        // Check if they are all in the home quad.
        if (location == NUMBER_OF_POINTS - 1)
        {
            if (actor == ACTOR::WHITE)
            {
                for (int i = 0; i < 19; i++)
                    if (board[i].second == ACTOR::WHITE)
                        return false;

                return true;
            }

            return false;
        }

        // Check if they are all in the home quad.
        if (location == 0)
        {
            if (actor == ACTOR::BLACK)
            {
                for (int i = NUMBER_OF_POINTS - 1; i > 5; i--)
                    if (board[i].second == ACTOR::BLACK)
                        return false;

                return true;
            }

            return false;
        }

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
        return dice_index < (6 * 6);
    }

    std::pair<int, int> next_dice_roll()
    {
        std::pair<int, int> next_roll = std::make_pair<int, int>(0, 0);

        assert(dice_index < 36);

        next_roll.first = (dice_index / 6) + 1;
        next_roll.second = (dice_index % 6) + 1;

        dice_index++;

        return next_roll;
    }
};

// TODO: Does not understand rules associated with rolling doubles.
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
            move_index = NUMBER_OF_POINTS - 1; // FIXME: Might need to be -1...
            move_step = -1;
        }
    }

    // FIXME: This doesn't fully check if there is a next move...
    bool has_next_move()
    {
        return 0 <= move_index && move_index <= NUMBER_OF_POINTS;
    }

    std::pair<int, int> next_move()
    {
        std::pair<int, int> next_move = std::make_pair<int, int>(-1, -1);

        assert(0 <= move_index && move_index <= NUMBER_OF_POINTS);

        // Find the next move.
        while (0 <= move_index && move_index <= NUMBER_OF_POINTS)
        {
            int to = move_index + (move_step * spaces_to_move);

            if (s.board[move_index].second == actor &&
                s.is_open(to, actor))
            {
                next_move.first = move_index;
                next_move.second = to;

                break;
            }

            move_index += move_step;
        }

        move_index += move_step;

        return next_move;
    }
};

int min(state s, int alpha, int beta);

int max(state s, int alpha, int beta)
{
    // Actor WHITE will always be moving
    // std::cout << s << alpha << beta << std::endl;

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
            state intermediate_state = state(s);
            intermediate_state.update_state(move.first, move.second);

            moves m2 = moves(roll.second, ACTOR::WHITE, intermediate_state);
            while (m2.has_next_move())
            {
                std::pair<int, int> move2 = m2.next_move();
                if (move2.first == -1)
                    continue;

                // Update state
                state next_state = state(intermediate_state);
                next_state.update_state(move2.first, move2.second);

                // std::cout << "Move: ( " << move.first << " -> " << move.second << " ) " << std::endl
                        //   << " ( " << move2.first << " -> " << move2.second << " ) " << std::endl;

                // Find the min value of that state.
                int value = min(next_state, alpha, beta);

                // If the min value is greater than the max value, update the max value.
                if (max_value_move.first < value)
                {
                    max_value_move.first = value;
                    max_value_move.second = action(move, move2);
                }

                if (alpha < max_value_move.first)
                {
                    alpha = max_value_move.first;
                }

                // If the min value is more than beta, return immediately.
                if (beta <= alpha)
                {
                    return max_value_move.first;
                }
            }
        }

        // Can add a check to see if roll.first == roll.second (Swapping order wouldn't matter)

        moves m1 = moves(roll.second, ACTOR::WHITE, s);
        while (m.has_next_move())
        {
            std::pair<int, int> move = m.next_move();
            if (move.first == -1)
                continue;

            // Update state
            state intermediate_state = state(s);
            intermediate_state.update_state(move.first, move.second);

            moves m2 = moves(roll.first, ACTOR::WHITE, intermediate_state);
            while (m2.has_next_move())
            {
                std::pair<int, int> move2 = m2.next_move();
                if (move2.first == -1)
                    continue;

                // Update state
                state next_state = state(intermediate_state);
                next_state.update_state(move2.first, move2.second);

                // Find the min value of that state.
                int value = min(next_state, alpha, beta);

                // If the min value is greater than the max value, update the max value.
                if (max_value_move.first < value)
                {
                    max_value_move.first = value;
                    max_value_move.second = action(move, move2);
                }

                if (alpha < max_value_move.first)
                {
                    alpha = max_value_move.first;
                }

                // If the min value is more than beta, return immediately.
                if (beta <= alpha)
                {
                    return max_value_move.first;
                }
            }
        }
    }

    // Return the max value and the action.
    return max_value_move.first;
}

int min(state s, int alpha, int beta)
{
    return -1;

    // Actor BLACK will always be moving
    std::cout << "MIN:" << std::endl
              << s << alpha << beta << std::endl;

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
            state intermediate_state = state(s);
            intermediate_state.update_state(move.first, move.second);

            moves m2 = moves(roll.second, ACTOR::BLACK, intermediate_state);
            while (m2.has_next_move())
            {
                std::pair<int, int> move2 = m2.next_move();
                if (move2.first == -1)
                    continue;

                // Make a modified game state instance.
                state next_state = state(intermediate_state);
                next_state.update_state(move2.first, move2.second);

                // Find the max value of that state.
                int value = max(next_state, alpha, beta);

                // If the max value is less than the min value, update the min value.
                if (value < min_value_move.first)
                {
                    min_value_move.first = value;
                    min_value_move.second = action(move, move2);
                }

                if (min_value_move.first < beta)
                {
                    beta = min_value_move.first;
                }

                // If the max value is less than alpha, return immediately.
                if (beta <= alpha)
                {
                    return min_value_move.first;
                }
            }
        }

        // Can add a check to see if roll.first == roll.second (Swapping order wouldn't matter)

        moves m1 = moves(roll.first, ACTOR::BLACK, s);
        while (m1.has_next_move())
        {
            std::pair<int, int> move = m1.next_move();
            if (move.first == -1)
                continue;

            // Update state
            state intermediate_state = state(s);
            intermediate_state.update_state(move.first, move.second);

            moves m2 = moves(roll.second, ACTOR::BLACK, intermediate_state);
            while (m2.has_next_move())
            {
                std::pair<int, int> move2 = m2.next_move();
                if (move2.first == -1)
                    continue;

                // Make a modified game state instance.
                state next_state = state(intermediate_state);
                next_state.update_state(move2.first, move2.second);

                // Find the max value of that state.
                int value = max(next_state, alpha, beta);

                // If the max value is less than the min value, update the min value.
                if (value < min_value_move.first)
                {
                    min_value_move.first = value;
                    min_value_move.second = action(move, move2);
                }

                if (min_value_move.first < beta)
                {
                    beta = min_value_move.first;
                }

                // If the max value is less than alpha, return immediately.
                if (beta <= alpha)
                {
                    return min_value_move.first;
                }
            }
        }
    }

    // Return the min value and the action.
    return min_value_move.first;
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