#include "drawGlyphs.hpp"
#include <Magick++.h>
#include <iostream>
#include <stdio.h>
#include <tuple>

struct Coord{
    int x = 0;
    int y = 0;
};
struct Placer{
    Coord coord;
    Magick::Image image;
};
enum Transform {Normal, Minify, Rotate90, Rotate180, Rotate270};

//base values
const int GLYPH_SIZE = 100; //must be a multiple of 20
const int SPACER = 5;

const int ART_OFFSET_X = -GLYPH_SIZE / 5;
const int ART_OFFSET_Y = -GLYPH_SIZE;
const int MINI_GLYPH_OFFSET = GLYPH_SIZE / 5;
const int MINI_GLYPH_SIZE = GLYPH_SIZE / 2;

Magick::Geometry MINI_GLYPH_GEO = Magick::Geometry(MINI_GLYPH_SIZE,MINI_GLYPH_SIZE);

std::tuple<int, int> prevCharOffset(char x){
    if (x == 'A' || x == 'E' || x == 'I' || x == 'O' || x == 'U' || x == 'Y')             //middle
        return std::make_tuple(MINI_GLYPH_SIZE / 2, -MINI_GLYPH_SIZE / 2);
    if (x == 'B' || x == 'C' || x == 'D' || x == 'F' || x == 'M' || x == 'N' || x == 'V') //top left
        return std::make_tuple(MINI_GLYPH_OFFSET, -MINI_GLYPH_OFFSET);
    if (x == 'L' || x == 'P')                                                             //top right
        return std::make_tuple(GLYPH_SIZE - (MINI_GLYPH_OFFSET + MINI_GLYPH_SIZE), -MINI_GLYPH_OFFSET);
    if (x == 'G' || x == 'H' || x == 'K' || x == 'T' || x == 'W')                         //bottom right
        return std::make_tuple(GLYPH_SIZE - (MINI_GLYPH_OFFSET + MINI_GLYPH_SIZE), MINI_GLYPH_OFFSET + MINI_GLYPH_SIZE - GLYPH_SIZE);
    if (x == 'R' || x == 'S' || x == 'X')                                                 //bottom left
        return std::make_tuple(MINI_GLYPH_OFFSET, MINI_GLYPH_OFFSET + MINI_GLYPH_SIZE - GLYPH_SIZE);
    return std::make_tuple(MINI_GLYPH_SIZE / 2,-MINI_GLYPH_SIZE / 2); // must be an unknown. place glyph in middle
}

Coord offset (Coord origin, int offsetx, int offsety){
    Coord offsetPos;
    offsetPos.x = origin.x + offsetx;
    offsetPos.y = origin.y + offsety;
    return offsetPos;
}

Magick::Image getImage(std::string str, Transform oper){
    Magick::Image image;
    try {
        image.read(str); //attempt to read file
    } catch (Magick::Exception &error){
        fprintf( stderr, "Caught exception: %s", error.what()); //might want to give it a special unknown glyph for it instead
    }
    if (oper == Minify)
        image.scale(Magick::Geometry(MINI_GLYPH_SIZE,MINI_GLYPH_SIZE));
    if (oper == Rotate180)
        image.rotate(180);
    return image;
}
Magick::Image getImage(std::string str){
    return getImage(str, Normal);
}


std::vector<Placer> place(std::vector<std::string> input){
    Coord homePos;
    std::vector<Placer> temp;
    char article = '0';
    for (unsigned int i = 0; i < input.size(); i++){
        std::string sequence = input[i];
        for (unsigned int j = 0; j < sequence.length(); j++){
            char x = sequence[j];
            if (x == '3')
                temp.push_back((Placer){homePos, getImage("../characters/_you.png")});
            if (x == '4')
                temp.push_back((Placer){homePos, getImage("../characters/_me.png")});
            if (x == '1' || x == '2')           // if there is an article
                article = x;                     // let the next glyph know to add it
            if (j == 0 && (x >= 'A' && x <= 'Z')) { //if first character of a thin or bold sequence add it as a main glyph
                char buf[21];
                sprintf(buf, "../characters/%c1.png", x);
                temp.push_back((Placer){homePos, getImage(buf)});
                if (article == '1')
                    temp.push_back((Placer){offset(homePos, ART_OFFSET_X, ART_OFFSET_Y), getImage("../characters/_the.png")});
                if (article == '2')
                    temp.push_back((Placer){offset(homePos, ART_OFFSET_X, ART_OFFSET_Y), getImage("../characters/_a.png")});
            }
            if (j == 1) {     //dont need to worry about it being 'A' through 'Z'
                char buf[21];
                sprintf(buf, "../characters/%c1.png", x);
                int offsetx;
                int offsety;
                std::tie(offsetx,offsety) = prevCharOffset(sequence[0]);
                temp.push_back((Placer){offset(homePos, offsetx, offsety), getImage(buf, Minify)});
            }
            if (j >= 2){
                //TODO add decos
            }
            if (j == (sequence.length()-1) && !(x == '1' || x == '2'))
                article = '0';
        }
        if (article == '0')                       // dont change the home position unless its a Glyph or Glyphset aka not an article
            homePos.x += (GLYPH_SIZE + SPACER);   // move the home position by the size of the glyph and the space between //no need to worry about y, thats not changing
    }
    return temp;
}

void resize(std::vector<Placer> pl, std::string tmpfile){
    int lowx = 0;
    int lowy = 0;
    int highx = 0;
    int highy = 0;
    for (unsigned int i = 0; i < pl.size(); i++){
        if (pl[i].coord.x < lowx){
            lowx = pl[i].coord.x;
        }
        if ((pl[i].coord.y - (int)pl[i].image.size().height()) < lowy){
            lowy = pl[i].coord.y - pl[i].image.size().height();
        }
        if (pl[i].coord.x + pl[i].image.size().width() > highx){
            highx = pl[i].coord.x + pl[i].image.size().width();
        }
        if (pl[i].coord.y > highy){
            highy = pl[i].coord.y;
        }
    }
    Magick::Image image(Magick::Geometry(highx - lowx, highy - lowy), Magick::Color("white"));
    for (unsigned int i = 0; i < pl.size(); i++){
        //pl[i].coord.x -= lowx;
        pl[i].coord.y *= -1;
        image.composite(pl[i].image, pl[i].coord.x, pl[i].coord.y, Magick::OverCompositeOp);
    }
    //Magick::Blob blob;  //ill understand blobs another day
    image.write(tmpfile);
}

void draw(std::vector<std::string> input, std::string tmpfile){
    std::vector<Placer> toPlace = place(input);
    resize(toPlace, tmpfile);
    return;
}
