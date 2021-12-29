#pragma once

#include <iostream>
#include <vector>
#include "utils.h"

class dice
{
private:
    std::vector<int> die_rolls;

public:
    dice() = default;
    ~dice() = default;
    static dice *generate_from_stream(std::istream &);
    friend std::ostream &operator<<(std::ostream &, dice &);
};