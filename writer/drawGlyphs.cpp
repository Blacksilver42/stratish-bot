#include "drawGlyphs.hpp"
#include <Magick++.h>
#include <iostream>
#include <stdio.h>
#include <climits>

struct Offset{
    int x;
    int y;
};
struct BluePrint{
    Offset offset;
    Magick::Image image;
};
enum Operation {None, Minify, Rotate90, Rotate180, Rotate270};

//base values
const int IMAGE_PADDING = 30;

const int GLYPH_SIZE = 100; //must be a multiple of 20
const int SPACER = 10;
const int THIN_DECO_SIZE = 40;
const int BOLD_DECO_SIZE = 20;
const int DECO_SPACER = 5;

const Offset ARTICLE_OFFSET = {-GLYPH_SIZE / 5, -GLYPH_SIZE};
const int MINI_GLYPH_OFFSET = (GLYPH_SIZE  * 3) / 20;
const int MINI_GLYPH_SIZE = GLYPH_SIZE / 2;

Magick::Geometry MINI_GLYPH_GEO = Magick::Geometry(MINI_GLYPH_SIZE,MINI_GLYPH_SIZE);

bool isBoldDeco(char x){
    return (x == 'A' || x == 'E' || x == 'I' || x == 'O' || x == 'U' || x == 'Y');
}

Offset charOffset(char x){
    if (x == 'A' || x == 'E' || x == 'I' || x == 'O' || x == 'U' || x == 'Y')             //middle
        return {MINI_GLYPH_SIZE / 2, -MINI_GLYPH_SIZE / 2};
    if (x == 'B' || x == 'C' || x == 'D' || x == 'F' || x == 'M' || x == 'N' || x == 'V') //top left
        return {MINI_GLYPH_OFFSET, -MINI_GLYPH_OFFSET};
    if (x == 'L' || x == 'P')                                                             //top right
        return {GLYPH_SIZE - (MINI_GLYPH_OFFSET + MINI_GLYPH_SIZE), -MINI_GLYPH_OFFSET};
    if (x == 'G' || x == 'H' || x == 'K' || x == 'T' || x == 'W' || x == 'Z')             //bottom right
        return {GLYPH_SIZE - (MINI_GLYPH_OFFSET + MINI_GLYPH_SIZE), MINI_GLYPH_OFFSET + MINI_GLYPH_SIZE - GLYPH_SIZE};
    if (x == 'R' || x == 'S' || x == 'X')                                                 //bottom left
        return {MINI_GLYPH_OFFSET, MINI_GLYPH_OFFSET + MINI_GLYPH_SIZE - GLYPH_SIZE};
    return {MINI_GLYPH_SIZE / 2,-MINI_GLYPH_SIZE / 2}; // must be an unknown. place glyph in middle
}

Offset offset (Offset origin, Offset offset){
    offset.x += origin.x;
    offset.y += origin.y;
    return offset;
}

Magick::Image getImage(std::string str, Operation oper){
    Magick::Image image;
    try {
        image.read(str); //attempt to read file
    } catch (Magick::Exception &error){
        fprintf( stderr, "Caught exception: %s", error.what()); //might want to give it a special unknown glyph for it instead
    }
    if (oper == Minify)
        image.scale(MINI_GLYPH_GEO);
    if (oper == Rotate180)
        image.rotate(180);
    return image;
}
Magick::Image getImage(std::string str){
    return getImage(str, None);
}


std::vector<BluePrint> graph(std::vector<std::string> input){
    Offset localOrigin = {0, 0};
    std::vector<BluePrint> bluePrint;
    char article = '0';
    for (unsigned int i = 0; i < input.size(); i++){
        std::string sequence = input[i];
        for (unsigned int j = 0; j < sequence.length(); j++){
            char x = sequence[j];
            if (x == '3')
                bluePrint.push_back({localOrigin, getImage("characters/_you.png")});
            if (x == '4')
                bluePrint.push_back({localOrigin, getImage("characters/_me.png")});
            if (x == '1' || x == '2')           // if there is an article
                article = x;                     // let the next glyph know to add it
            if (j == 0 && (x >= 'A' && x <= 'Z')) { //if first character of a thin or bold sequence add it as a main glyph
                char buf[18];
                sprintf(buf, "characters/%c1.png", x);
                bluePrint.push_back({localOrigin, getImage(buf)});
                if (article == '1')
                    bluePrint.push_back({offset(localOrigin, ARTICLE_OFFSET), getImage("characters/_the.png")});
                if (article == '2')
                    bluePrint.push_back({offset(localOrigin, ARTICLE_OFFSET), getImage("characters/_a.png")});
            }
            if (j == 1) {     //dont need to worry about it being 'A' through 'Z'
                char buf[18];
                sprintf(buf, "characters/%c1.png", x);
                Offset offsetPrev = charOffset(sequence[0]);
                bluePrint.push_back({offset(localOrigin, offsetPrev), getImage(buf, Minify)});
            }
            if (j >= 2){
                char buf[18];
                sprintf(buf, "characters/%c2.png", x);
                if (j % 2 == 0 && article == '0'){ //add on bottom
                    if (isBoldDeco(x))
                        bluePrint.push_back({offset(localOrigin,{0 ,static_cast<int>(-GLYPH_SIZE - DECO_SPACER - (j - 2) * (DECO_SPACER + BOLD_DECO_SIZE))}), getImage(buf, Rotate180)});
                    else
                        bluePrint.push_back({offset(localOrigin,{0 ,static_cast<int>(-GLYPH_SIZE - DECO_SPACER - (j - 2) * (DECO_SPACER + THIN_DECO_SIZE))}), getImage(buf, Rotate180)});
                }
                if (j % 2 == 1 || article != '0'){ //add on 
                    if (isBoldDeco(x))
                        bluePrint.push_back({offset(localOrigin,{0 ,static_cast<int>((j - 1) * (DECO_SPACER + BOLD_DECO_SIZE))}), getImage(buf)});
                    else
                        bluePrint.push_back({offset(localOrigin,{0 ,static_cast<int>((j - 1) * (DECO_SPACER + THIN_DECO_SIZE))}), getImage(buf)});
                }
                //TODO add decos
            }
            if (j == (sequence.length()-1) && !(x == '1' || x == '2'))
                article = '0';
        }
        if (article == '0')                       // dont change the home position unless its a Glyph or Glyphset aka not an article
            localOrigin.x += (GLYPH_SIZE + SPACER);   // move the localOrigin by the size of the glyph and the space between //no need to worry about y, thats not changing
    }
    return bluePrint;
}

Offset correctOffsets(std::vector<BluePrint> &bluePrint){
    int lowx = 0;
    int lowy = 0;
    int highx = 0;
    int highy = 0;
    for (unsigned int i = 0; i < bluePrint.size(); i++){
        if (bluePrint[i].offset.x < lowx){
            lowx = bluePrint[i].offset.x;
        }
        if ((int)(bluePrint[i].offset.y - (int)(bluePrint[i].image.size().height() & INT_MAX)) < lowy){
            lowy = (int)bluePrint[i].offset.y - (int)bluePrint[i].image.size().height();
        }
        if ((int)(bluePrint[i].offset.x + (int)(bluePrint[i].image.size().width() & INT_MAX)) > highx){
            highx = (int)bluePrint[i].offset.x + (int)bluePrint[i].image.size().width();
        }
        if (bluePrint[i].offset.y > highy){
            highy = bluePrint[i].offset.y;
        }
    }
    for (unsigned int i = 0; i < bluePrint.size(); i++){
        bluePrint[i].offset.x -= lowx;
        bluePrint[i].offset.y *= -1;
        bluePrint[i].offset.y += highy;
        bluePrint[i].offset.x += IMAGE_PADDING;
        bluePrint[i].offset.y += IMAGE_PADDING;
    }
    return {highx - lowx + 2 * IMAGE_PADDING, highy - lowy + 2 * IMAGE_PADDING};
}

void drawToFile(std::vector<std::string> input, std::string tmpfile){
    Magick::InitializeMagick(NULL);
    std::vector<BluePrint> bluePrint = graph(input);
    Offset size = correctOffsets(bluePrint);
    Magick::Image image(Magick::Geometry(size.x, size.y), Magick::Color("white"));
    for (unsigned int i = 0; i < bluePrint.size(); i++)
        image.composite(bluePrint[i].image, bluePrint[i].offset.x, bluePrint[i].offset.y, Magick::OverCompositeOp);
    image.write(tmpfile);
    return;
}
