#pragma once

#include <iostream>

#include "gameboard.h"
#include "dice.h"
#include "utils.h"

class game_state
{
private:
    color color_of_actor;
    // TODO: Update to use smart pointers
    gameboard *gameboard_instance;
    dice *die_rolls;

public:
    game_state() = default;
    ~game_state() = default;

    game_state(const game_state &) = delete;
    game_state &operator= (const game_state &) = delete;
    game_state(game_state &&) = delete;
    game_state &operator= (game_state &&) = delete;

    bool is_game_over();
    int utility();
    std::vector<game_state *> *generate_possible_next_states();
    static game_state *generate_from_stream(std::istream &);

    friend std::ostream &operator<<(std::ostream &, game_state &);
};