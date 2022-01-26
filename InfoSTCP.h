//
// Created by Diogo Babo on 25/01/2022.
//

#ifndef PROJETO2_AED_INFOSTCP_H
#define PROJETO2_AED_INFOSTCP_H

#include <string>
#include <vector>
#include "Line.h"
#include "bst.h"
#include "Stop.h"
#include <cmath>
#include "GetDataSet.h"
#include "graph.h"
#include <iostream>

class InfoSTCP {
private:
    std::vector<Stop *> stopsvec;
    static double haversine(Stop* stop1,Stop* stop2);
    std::map<std::string,int> stopMap;
    Graph graph;
public:
    InfoSTCP();
    void readLines(std::string filename);
    void start();

};


#endif //PROJETO2_AED_INFOSTCP_H
