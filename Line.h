//
// Created by Diogo Babo on 18/01/2022.
//

#ifndef PROJETO2_AED_LINE_H
#define PROJETO2_AED_LINE_H


#include <string>

class Stop;

class Line {
private:
    std::string name;
    std::string code;
    Stop *dest;
    bool atNight;
    double distance;
public:
    enum TYPE{
        AUTOCARRO,
        ELETRICO,
        WALKING,
        START
    };
    bool null;
    TYPE type;
    Line(std::string code,std::string name,Stop *dest,bool atNight,double distance,TYPE type);
    Line(TYPE type);
    void setName(std::string name);
    void setCode(std::string code);
    void setDest(Stop *dest);
    void setNight();
    void setType(TYPE type);
    void setDistance(double distance);
    std::string getName();
    std::string getCode();
    Stop* getDest();
    bool getNight();
    TYPE getType();
    double getDistance();
    double weight;
};


#endif //PROJETO2_AED_LINE_H
