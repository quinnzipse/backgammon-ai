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

    point(const point &) = delete;
    point &operator=(const point &) = delete;
    point(point &&) = delete;
    point &operator=(point &&) = delete;

    bool is_open(color);
    void fill_from_stream(std::istream &);

    friend std::ostream &operator<<(std::ostream &, point &);
};