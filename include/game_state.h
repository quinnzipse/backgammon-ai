#pragma once

#include <iostream>
#include <vector>
#include "facts.h"
#include "gameboard.h"
#include "dice.h"

class game_state
{
private:
    color color_of_actor;
    gameboard *gameboard_instance;
    dice *die_rolls;

public:
    game_state() = default;
    ~game_state() = default;
    static game_state *generate_from_stream(std::istream &);
    friend std::ostream &operator<<(std::ostream &, game_state &);
};