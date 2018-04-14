#pragma once
#include <iostream>

#include "error.hpp"

struct Info{
    std::string input;
    std::string font;
};

Error getInfo(int argc, char* argv[], Info &info);
