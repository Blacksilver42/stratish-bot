#include "drawGlyphs.hpp"
#include <Magick++.h>
#include <iostream>

struct Coord{
    int x = 0;
    int y = 0;
};
struct Placer{
    Coord coord;
    std::string imageLoc;     //image location "glyph/A.png","deco/A.png", "special/the.png"
};

//base values
int GLYPH_SIZE = 40;
int SPACER = 6;

Magick::Geometry MINI_GLYPH_GEO = Magick::Geometry(30,30);

std::vector<Placer> place(std::vector<std::string> input){
    Coord homePos;
    std::vector<Placer> temp;
    char article = '0';
    for (int i = 0; i < input.size(); i++){
        std::string sequence = input[i];
        for (int j = 0; j < sequence.length(); j++){
            char x = sequence[j];
            if (x == '3')
                temp.push_back((Placer){homePos, "../characters/_you.png"});
            if (x == '4')
                temp.push_back((Placer){homePos, "../characters/_i.png"});
            if (x == '1' || x == '2'){           // if there is an article
                article = x;                     // let the next glyph know to add it
            if (j == 0 && (x >= 'A' && x <= 'Z')) { //if first character of a thin or bold sequence add it as a main glyph
                char buf[20];
                sprintf(buf, "../characters/%c.png", x);
                temp.push_back((Placer){homePos, buf});
            }
            }
        }
        if (article != '0')                       // dont change the home position unless its a Glyph or Glyphset aka not an article
            homePos.x += (GLYPH_SIZE + SPACER);   // move the home position by the size of the glyph and the space between //no need to worry about y, thats not changing
    }
    return temp;
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
