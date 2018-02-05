#include <iostream>
#include <stdio.h>
#include "format.hpp"
#include "drawGlyphs.hpp"

int main(int argc, char* argv[]) {
	// not enough args? give up.
    if (argc < 3) return 1;
	
	// seperate the words
    std::vector<std::string> formatted = format(argv[1]);

	// xyzzy!
    drawToFile(formatted, argv[2]);
}

