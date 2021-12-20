#pragma once

#include <istream>

#include "facts.h"
#include "utils.h"

class point
{
public:
    point();
    point(int, color);
    // ~point();
    bool is_open(color);
    static point generate_from_stream(std::istream &);
    friend std::ostream &operator<<(std::ostream &, point &);

private:
    int number_of_checkers;
    color color_of_checkers;
};