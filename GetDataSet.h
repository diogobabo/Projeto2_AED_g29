//
// Created by Diogo Babo on 18/01/2022.
//

#ifndef PROJETO2_AED_GETDATASET_H
#define PROJETO2_AED_GETDATASET_H

#include <sstream>
#include <fstream>
#include "bst.h"
#include "Stop.h"


class GetDataSet {
private:
    BST<Stop *> bstStop =  BST<Stop *>(new Stop("","","",0,0));

public:
    GetDataSet(std::string stopFile);
    BST<Stop *> &getStops();
};


#endif //PROJETO2_AED_GETDATASET_H
