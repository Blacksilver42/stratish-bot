#include <sstream>
#include <iostream>
#include <vector>
#include "format.hpp"

bool isBold(char x){
    return (x == 'A' || x == 'E' || x == 'I' || x == 'O' || x == 'U' || x == 'Y');
}
bool isThin(char x){
    return (!(isBold(x)) && (x >= 'A' && x <= 'Z'));
}

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
        if (!((x >= 'A' && x <= 'Z') || x == ' ' || x == 0)){ //if not any char I care about, discard
            i++;
            continue;
        }
        if(isBold(x))
            tempBold << (char)x;
        if(isThin(x))
            tempThin << (char)x;
        if(x == ' ' || x == 0){
            if (tempWord.str() == "THE"){
                groups.push_back("t");
            } else
            if (tempWord.str() == "A"){
                groups.push_back("a");
            } else
            if (tempWord.str() == "YOU"){
                groups.push_back("y");
            } else
            if (tempWord.str() == "I"){
                groups.push_back("i");
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
