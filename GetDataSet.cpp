//
// Created by Diogo Babo on 18/01/2022.
//


#include "GetDataSet.h"

GetDataSet::GetDataSet(std::string stopFile) {
    std::fstream StopFile(stopFile);
    if(!StopFile.is_open()){
        exit(EXIT_FAILURE);
    }
    std::string stopString;
    getline(StopFile,stopString);
    while(getline(StopFile,stopString)){

        std::stringstream str(stopString);

        std::string code,name,zone,la,lo;

        getline(str,code,',');
        getline(str,name,',');
        getline(str,zone,',');
        getline(str,la,',');
        getline(str,lo,',');

        Stop stop1(code,name,zone,stod(la),stod(lo));
        Stop * stop = new Stop(stop1);
        bstStop.insert(stop);
    }

}

BST<Stop *> &GetDataSet::getStops() {
    return bstStop;
}
