#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "utils.h"

class dice
{
private:
    std::vector<int> die_rolls;

public:
    dice() = default;
    ~dice() = default;

    dice(const dice &) = delete;
    dice &operator=(const dice &) = delete;
    dice(dice &&) = delete;
    dice &operator=(dice &&) = delete;

    static std::shared_ptr<dice> generate_from_stream(std::istream &);

    friend std::ostream &operator<<(std::ostream &, dice &);
};