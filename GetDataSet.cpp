
#include "GetDataSet.h"

GetDataSet::GetDataSet(std::string stopFile) {
    std::fstream StopFile(stopFile);
    if(!StopFile.is_open()){
        exit(EXIT_FAILURE);
    }
    std::string stopString;
    getline(StopFile,stopString);
    int counter = 0;
    while(getline(StopFile,stopString)){
        counter++;
        std::stringstream str(stopString);

        std::string code,name,zone,la,lo;

        getline(str,code,',');
        getline(str,name,',');
        getline(str,zone,',');
        getline(str,la,',');
        getline(str,lo,',');

        Stop stop1(counter,code,name,zone,stod(la),stod(lo));
        Stop * stop = new Stop(stop1);
        stopsvec.push_back(stop);
        mappedValues.insert(std::pair<std::string ,int>(code,counter));
    }
    StopFile.close();
}

std::vector<Stop *> &GetDataSet::getStops() {
    return stopsvec;
}

std::map<std::string, int> &GetDataSet::getMap() {
    return mappedValues;
}
