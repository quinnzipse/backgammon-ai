#pragma once

#include <istream>
#include <vector>

#include "point.h"
#include "game_state.h"

const int NUMBER_OF_POINTS = 26;
const int NUMBER_OF_COLOR_CHECKERS = 15;
class gameboard
{
private:
    point points[NUMBER_OF_POINTS];
    int white_checkers_on_bar;
    int black_checkers_on_bar;

    gameboard() = default;

public:
    ~gameboard() = default;

    gameboard(const gameboard &) = delete;
    gameboard &operator= (const gameboard &) = delete;
    gameboard(gameboard &&) = delete;
    gameboard &operator= (gameboard &&) = delete;

    bool is_game_over();
    std::vector<game_state *> *generate_possible_next_states();
    static gameboard *generate_from_stream(std::istream &);
    
    friend std::ostream &operator<<(std::ostream &, gameboard &);
};