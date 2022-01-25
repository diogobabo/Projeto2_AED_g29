//
// Created by Diogo Babo on 18/01/2022.
//

#include "Stop.h"


Stop::Stop(std::string Code, std::string Name, std::string Zone, double Latitude, double Longitude) : Code(Code),Name(Name),Zone(Zone),Latitude(Latitude),Longitude(Longitude) {

}

void Stop::addOutgoingLine(Line line) {
    this->adj.push_back(line);
}
