//
// Created by Diogo Babo on 18/01/2022.
//

#ifndef PROJETO2_AED_LINE_H
#define PROJETO2_AED_LINE_H


#include <string>
#include "Stop.h"

class Line {
private:
    enum TYPE{
        AUTOCARRO,
        ELETRICO
    };
    std::string name;
    std::string code;
    Stop dest;
    bool atNight;
    TYPE type;
public:
    Line(std::string code,std::string name,Stop dest,bool atNight,TYPE type);
};


#endif //PROJETO2_AED_LINE_H
