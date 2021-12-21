#include <iostream>
#include <vector>
#include "facts.h"
#include "gameboard.h"

class game_state
{
private:
    std::vector<int> die_rolls;
    color color_of_actor;
    gameboard *gameboard_instance;

public:
    game_state();
    ~game_state();
    static game_state *generate_from_stream(std::istream &);
    friend std::ostream &operator<<(std::ostream &, game_state &);
};