//
// Created by Diogo Babo on 18/01/2022.
//

#ifndef PROJETO2_AED_GETDATASET_H
#define PROJETO2_AED_GETDATASET_H

#include <sstream>
#include <fstream>
#include "Stop.h"
#include <map>

class GetDataSet {
private:
    std::vector<Stop *> stopsvec;

    std::map<std::string,int> mappedValues;

public:
    GetDataSet(std::string stopFile);
    std::vector<Stop *> &getStops();
    std::map<std::string,int> &getMap();
};


#endif //PROJETO2_AED_GETDATASET_H
