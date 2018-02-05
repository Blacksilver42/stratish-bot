#ifndef DRAWGLYPHS_HPP
#define DRAWGLYPHS_HPP

#include <string>
#include <vector>
#include <iostream>
#include <Magick++.h>

struct Offset{
    int x;
    int y;
};

struct BluePrint{
    Offset offset;
    Magick::Image image;
};

enum Operation {None, Minify, Rotate90, Rotate180, Rotate270};

void drawToFile(std::vector<std::string> input, std::string tmpfile);
#endif
