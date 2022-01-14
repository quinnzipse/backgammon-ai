#pragma once

#include <istream>
#include <vector>
#include <memory>

#include "point.h"

const size_t NUMBER_OF_POINTS = 26;
const int NUMBER_OF_COLOR_CHECKERS = 15;

class gameboard
{
private:
    std::shared_ptr<std::vector<point>> points;
    int white_checkers_on_bar;
    int black_checkers_on_bar;

public:
    gameboard(std::shared_ptr<std::vector<point>> , int, int);

    ~gameboard() = default;

    gameboard() = delete;
    gameboard(const gameboard &) = delete;
    gameboard &operator=(const gameboard &) = delete;
    gameboard(gameboard &&) = delete;
    gameboard &operator=(gameboard &&) = delete;

    bool is_game_over();
    std::shared_ptr<std::vector<gameboard *>> generate_possible_next_states();
    static std::shared_ptr<gameboard> generate_from_stream(std::istream &);

    friend std::ostream &operator<<(std::ostream &, gameboard &);
};