//
// Created by Diogo Babo on 18/01/2022.
//

#include "Line.h"

Line::Line(std::string code, std::string name, Stop dest, bool atNight, double distance,Line::TYPE type) : code(code),name(name), dest(dest),atNight(atNight),type(type), distance(distance){
}
