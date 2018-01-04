#include <iostream>
#include "format.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::vector<std::string> formatted = format(argv[1]);
    //std::cout << draw(formatted);
    for (std::string word: formatted)
        printf("%s, size:%lu\n", word.c_str(), word.size());
    return 0;
}

