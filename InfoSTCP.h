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
#include <iostream>

class InfoSTCP {
private:
    BST<Stop *> bstStop =  BST<Stop *>(new Stop("","","",0,0));
    static double haversine(Stop* stop1,Stop* stop2);
public:
    InfoSTCP();
    std::vector <Line> lines;
    void readLines(std::string filename);
    void start();

};


#endif //PROJETO2_AED_INFOSTCP_H
