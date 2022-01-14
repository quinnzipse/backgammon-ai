#pragma once

#include <istream>

#include "utils.h"

class point
{
private:
    int number_of_checkers;
    color color_of_checkers;

public:
    point();

    ~point() = default;
    point(const point &) = default;
    point &operator=(const point &) = default;
    point(point &&) = default;
    point &operator=(point &&) = default;

    bool is_open(color);
    void fill_from_stream(std::istream &);

    friend std::ostream &operator<<(std::ostream &, point &);
};