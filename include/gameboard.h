#pragma once

#include <istream>

#include "point.h"

const int NUMBER_OF_POINTS = 26;
class gameboard
{
private:
    point points[NUMBER_OF_POINTS];
    gameboard();
    // Need to figure out how to represent the bar and the home

public:
    static gameboard *generate_from_stream(std::istream &);
    friend std::ostream &operator<<(std::ostream &, gameboard &);
};