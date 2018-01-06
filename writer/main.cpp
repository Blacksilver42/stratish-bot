#include <iostream>
#include <stdio.h>
#include "format.hpp"
#include "drawGlyphs.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    std::vector<std::string> formatted = format(argv[1]);
    draw(formatted, argv[2]);
}

