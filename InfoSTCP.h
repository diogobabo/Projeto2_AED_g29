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

class InfoSTCP {
private:
    BST<Stop *> bstStop =  BST<Stop *>(new Stop("","","",0,0));
public:
    InfoSTCP();
    std::vector <Line> lines;
    void readLines(std::string filename);
    void start();

};


#endif //PROJETO2_AED_INFOSTCP_H
