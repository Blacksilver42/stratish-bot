#include "drawGlyphs.hpp"
#include <Magick++.h>
#include <iostream>

struct Coord{
        int x = 0;
        int y = 0;
};
struct Placer{
    Coord coord;
    char ii;
};

Magick::Geometry MINI_GLYPH_GEO = Magick::Geometry(30,30);

std::vector<std::tuple<int, int, Magick::Image>> place(std::vector<std::string> input){
    Coord homePos;
    return;
}

void draw(std::vector<std::string> input){
    place(input);
    Magick::Image image;
    Magick::Blob blob;
    //image.resize();
    image.write(&blob);
    std::cout << blob.data();
    return;
}

Magick::Image glyph(char x){
    Magick::Image image;
    char buf[14];
    sprintf(buf, "images/%c1.png", x);
    image.read(buf);
    return image;
}
Magick::Image miniGlyph(char x){
    Magick::Image image = glyph(x);
    image.scale(MINI_GLYPH_GEO);
    return image;
}
Magick::Image decoration(char x){
    Magick::Image image;
    char buf[14];
    sprintf(buf, "images/%c2.png", x);
    image.read(buf);
    return image;
}
