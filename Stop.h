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
    std::string code,name,zone;
    double latitude,longitude;
    std::vector<Line> adj;
public:
    Stop(std::string Code,std::string name,std::string zone,double latitude,double longitude);
    void addOutgoingLine(Line line);
    void setName(std::string name);
    void setCode(std::string code);
    void setZone(std::string zone);
    void setLatitude(double lat);
    void setLongitude(double lon);
    std::string getCode();
    std::string getName();
    std::string getZone();
    double getLatitude();
    double getLongitude();

};


#endif //PROJETO2_AED_STOP_H
