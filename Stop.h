//
// Created by Diogo Babo on 18/01/2022.
//

#ifndef PROJETO2_AED_STOP_H
#define PROJETO2_AED_STOP_H


#include <string>
#include <vector>
#include "Line.h"

class Stop {
private:
    std::string Code,Name,Zone;
    double Latitude,Longitude;
    std::vector<Line> adj;
public:
    Stop(std::string Code,std::string Name,std::string Zone,double Latitude,double Longitude);
    void addOutgoingLine(Line line);

};


#endif //PROJETO2_AED_STOP_H
