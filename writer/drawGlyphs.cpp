#include "drawGlyphs.hpp"
#include <Magick++.h>
#include <iostream>
#include <stdio.h>
#include <climits>

#include "presets.h"

struct Offset{
    int x;
    int y;
};

struct BluePrint{
    Offset offset;
    Magick::Image image;
};

enum Operation {None, Minify, Rotate90, Rotate180, Rotate270};


const Offset ARTICLE_OFFSET = {-GLYPH_SIZE / 5, -GLYPH_SIZE};

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
        if (sequence.length() == 0)
            continue;
        int decorationSize;
        Offset localDecoTopOrigin;
        Offset localDecoBotOrigin;
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
            if (j == 2){
                if (isBoldDeco(x))
                    decorationSize = BOLD_DECO_SIZE;
                else
                    decorationSize = THIN_DECO_SIZE;
                localDecoTopOrigin = offset(localOrigin, {0, decorationSize + DECO_SPACER});
                localDecoBotOrigin = offset(localOrigin, {0, -GLYPH_SIZE - DECO_SPACER});
            }
            if (j >= 2){
                char buf[18];
                sprintf(buf, "characters/%c2.png", x);
                if (j % 2 == 0 && article == '0'){ //add on bottom
                    bluePrint.push_back({localDecoBotOrigin, getImage(buf, Rotate180)});
                    localDecoBotOrigin.y -= (decorationSize + DECO_SPACER);
                }
                if (j % 2 == 1 || article != '0'){ //add on 
                    bluePrint.push_back({localDecoTopOrigin, getImage(buf)});
                    localDecoTopOrigin.y += (decorationSize + DECO_SPACER);
                }
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
