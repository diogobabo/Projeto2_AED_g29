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
    std::vector<Stop *> stopsVec;
    std::vector<Line *> lineVec;
    std::vector<Line *> artificialLineVec;
    static double haversine(Stop* stop1,Stop* stop2);
    std::map<std::string,int> stopMap;
    Graph graph;
    double maxWalkingDistance;
    void functionTest();
    void reduceArtificialLineVec();
    void enlargeArtificialLineVec(double lastWalkingDistance);
public:
    InfoSTCP();
    void setNewWalkDistance(double newWalkingDistance);
    void readLines(std::string filename);
    void start();
    void addStop(std::string code, std::string name, std::string zone, long lat, long lon);
    void addLine();
    void checkInput();

};


#endif //PROJETO2_AED_INFOSTCP_H
