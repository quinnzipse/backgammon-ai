#include "facts.h"

class point
{
public:
    point();
    point(int, color);
    ~point();
    int is_open(color color_of_actor);

private:
    int number_of_checkers;
    color color_of_checkers;
};