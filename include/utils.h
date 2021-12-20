#pragma once

#include <istream>
#include <string>

#include "facts.h"

color read_color_from_stream(std::istream &input_stream);

int read_next_int_from_stream(std::istream &input_stream);