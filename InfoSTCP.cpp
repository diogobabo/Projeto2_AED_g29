//
// Created by Diogo Babo on 25/01/2022.
//

#include "InfoSTCP.h"

void InfoSTCP::readLines(std::string filename) {
    std::fstream lineFile;
    std::fstream lineSpec;
    lineFile.open(filename);
    if(!lineFile) {
        exit(EXIT_FAILURE);
    }
    std::string s;
    getline(lineFile,s);
    while(getline(lineFile,s)) {
        std::string code,name;
        std::stringstream str(s);
        std::fstream lineDir;
        std::string nomeFicheiro = "../dataset/line";
        getline(str,code,',');
        getline(str,name,',');
        nomeFicheiro += "_" + code + "_" + "0.csv";

        // LER FICHEIRO 0
        lineDir.open(nomeFicheiro);
        if(!lineDir) {
            exit(EXIT_FAILURE);
        }
// CONSTRUIR LINHAS PARA STOPS

        std::string codeStop;
        getline(lineDir,codeStop);// ignorar primeira linha

        while(getline(lineDir,codeStop)) { //aqui dentro crias as linhas
            std::cout << codeStop << std::endl;
        }
        lineDir.close();

        // LER FICHEIRO 1
        nomeFicheiro.replace(nomeFicheiro.size() - 5,1,"1");
        lineDir.open(nomeFicheiro);
        if(!lineDir){
            exit(EXIT_FAILURE);
        }

        getline(lineDir,codeStop); // ignorar primeira linha
        while(getline(lineDir,codeStop)) { //aqui dentro crias as linhas
            std::cout << codeStop << std::endl;
        }
        lineDir.close();

    }

}

InfoSTCP::InfoSTCP() {
    GetDataSet getbst("../dataset/stops.csv");
    bstStop = getbst.getStops();
    readLines("../dataset/lines.csv");

}
double InfoSTCP::haversine(Stop* stop1,Stop* stop2)
{
    // distance between latitudes
    // and longitudes
    double lat2 = stop2->getLatitude(),lat1= stop1->getLatitude(),lon2= stop2->getLongitude(),lon1= stop1->getLongitude();
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void InfoSTCP::start() {

}
