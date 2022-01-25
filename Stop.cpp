//
// Created by Diogo Babo on 18/01/2022.
//

#include "Stop.h"


Stop::Stop(std::string code, std::string name, std::string zone, double latitude, double longitude) : code(code),name(name),zone(zone),latitude(latitude),longitude(longitude) {

}

void Stop::addOutgoingLine(Line line) {
    this->adj.push_back(line);
}

void Stop::setName(std::string name) {
    this->name = name;
}

void Stop::setCode(std::string code) {
    this->code = code;
}

void Stop::setZone(std::string zone) {
    this->zone=zone;
}

void Stop::setLatitude(double lat) {
    this->latitude=lat;
}

void Stop::setLongitude(double lon) {
    this->longitude=lon;
}

std::string Stop::getCode() {
    return code;
}

std::string Stop::getName() {
    return name;
}

std::string Stop::getZone() {
    return zone;
}

double Stop::getLatitude() {
    return latitude;
}

double Stop::getLongitude() {
    return longitude;
}

