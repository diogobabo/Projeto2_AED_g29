
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
    /**
    * Constructor of the class
    * @param stopFile: csv file
    **/
    GetDataSet(std::string stopFile);

    /**
    * returns the vector of all stops
    * @returns vector of pointers to stop
    */
    std::vector<Stop *> &getStops();

    /**
    * returns the map(code->number)
    * @returns vector of pointers to stop
    */
    std::map<std::string,int> &getMap();
};


#endif //PROJETO2_AED_GETDATASET_H
