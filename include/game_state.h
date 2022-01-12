#pragma once

#include <iostream>
#include <memory>

#include "gameboard.h"
#include "dice.h"
#include "utils.h"

class game_state
{
private:
    color color_of_actor;
    std::shared_ptr<gameboard> gameboard_instance;
    std::shared_ptr<dice> die_rolls;

public:
    game_state() = default;
    ~game_state() = default;

    game_state(const game_state &) = delete;
    game_state &operator= (const game_state &) = delete;
    game_state(game_state &&) = delete;
    game_state &operator= (game_state &&) = delete;

    bool is_game_over();
    int utility();
    std::shared_ptr<std::vector<game_state *>> generate_possible_next_states();
    static std::shared_ptr<game_state> generate_from_stream(std::istream &);

    friend std::ostream &operator<<(std::ostream &, game_state &);
};