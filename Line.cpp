//
// Created by Diogo Babo on 18/01/2022.
//

#include "Line.h"
#include "Stop.h"

Line::Line(std::string code, std::string name, Stop *dest, bool atNight, double distance,Line::TYPE type) : code(code),name(name), dest(dest),atNight(atNight),type(type), distance(distance){
    weight = 0;
}

void Line::setName(std::string name) {
    this->name = name;
}

void Line::setCode(std::string code) {
    this->code = code;
}

void Line::setDest(Stop *dest) {
    this->dest=dest;
}

void Line::setNight() {
    this->atNight = true;
}

void Line::setType(Line::TYPE type) {
    this->type = type;
}

void Line::setDistance(double distance) {
    this->distance = distance;
}

std::string Line::getName() {
    return name;
}

std::string Line::getCode() {
    return code;
}

Stop* Line::getDest() {
    return dest;
}

bool Line::getNight() {
    return atNight;
}

Line::TYPE Line::getType() {
    return type;
}

double Line::getDistance() {
    return distance;
}

Line::Line(Line::TYPE type) {
    this->type = type;
}
