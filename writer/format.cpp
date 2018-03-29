#include <sstream>
#include <iostream>
#include <vector>
#include "format.hpp"
#include "common.hpp"

std::vector<std::string> format(char* input){
    std::vector<std::string> groups;
    std::stringstream tempBold;
    std::stringstream tempThin;
    std::stringstream tempWord;
    char x = 1;
    int i = 0;
    while (x > 0){
        x = input[i];
        if (x >= 'a' && x <= 'z') //make it uppercase
            x -= 32;
        if (!((x >= 'A' && x <= 'Z') || x == ' ' || x == '-' || x == '_' || x == 0)){ //if not any char I care about, discard
            i++;
            continue;
        }
        if(isBold(x))
            tempBold << (char)x;
        if(isThin(x))
            tempThin << (char)x;
        if(x == ' ' || x == 0){
            if (tempWord.str() == "THE"){ // Maybe cryptic, but this is easier so I dont have to make an actual parser or pass an enum
                groups.push_back("1");
            } else
            if (tempWord.str() == "A"){
                groups.push_back("2");
            } else
            if (tempWord.str() == "YOU"){
                groups.push_back("3");
            } else
            if (tempWord.str() == "I"){
                groups.push_back("4");
            } else
            if (!(tempWord.str().empty())){
                groups.push_back(tempThin.str());
                groups.push_back(tempBold.str());
            }
            
            // clear temps
            tempWord.str("");
            tempWord.clear();
            tempThin.str("");
            tempThin.clear();
            tempBold.str("");
            tempBold.clear();
        } else {
            tempWord << (char)x;
        }
        i++;
    }
    return groups;
}
