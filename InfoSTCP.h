//
// Created by Diogo Babo on 25/01/2022.
//

#ifndef PROJETO2_AED_INFOSTCP_H
#define PROJETO2_AED_INFOSTCP_H

#include <string>
#include <vector>
#include "Line.h"


class InfoSTCP {
public:
    std::vector <Line> lines;
    void readLines(std::string filename);

};


#endif //PROJETO2_AED_INFOSTCP_H
