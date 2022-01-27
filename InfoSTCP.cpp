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
        bool night = false;
        std::string code,name;

        std::stringstream str(s);
        std::fstream lineDir;
        std::string nomeFicheiro = "../dataset/line";

        getline(str,code,',');
        getline(str,name,',');

        nomeFicheiro += "_" + code + "_" + "0.csv";

        if(code.at(code.length() - 1) == 'M') {
            night = true;
        }

        // LER FICHEIRO 0
        lineDir.open(nomeFicheiro);
        if(!lineDir) {
            exit(EXIT_FAILURE);
        }
// CONSTRUIR LINHAS PARA STOPS

        std::string codeStop;
        getline(lineDir,codeStop);// ignorar primeira linha
        int lineNumber = stoi(codeStop);

        getline(lineDir,codeStop);

        int stopNumberSRC = (stopMap.find(codeStop))->second;
        Stop *src = stopsvec.at(stopNumberSRC);

        for(int var = 1; var<lineNumber; var++) { //aqui dentro crias as linhas
            getline(lineDir,codeStop);

            int stopNumberDEST = (stopMap.find(codeStop))->second;
            Stop *dest = stopsvec.at(stopNumberDEST);
            Line line1(code,name,dest,night, haversine(src,dest),Line::AUTOCARRO);
            Line *line = new Line(line1);
            graph.addEdge(stopNumberSRC,line);

            stopNumberSRC = stopNumberDEST;
            src = dest;
        }
        lineDir.close();

        // LER FICHEIRO 1
        nomeFicheiro.replace(nomeFicheiro.size() - 5,1,"1");
        lineDir.open(nomeFicheiro);
        if(!lineDir){
            exit(EXIT_FAILURE);
        }

        getline(lineDir,codeStop); // ignorar primeira linha

        lineNumber = stoi(codeStop);
        if(lineNumber == 0){
            lineDir.close();
            continue;
        }
        getline(lineDir,codeStop);

        stopNumberSRC = (stopMap.find(codeStop))->second;
        src = stopsvec.at(stopNumberSRC);

        for(int var = 1; var<lineNumber; var++) { //aqui dentro crias as linhas
            getline(lineDir,codeStop);

            int stopNumberDEST = (stopMap.find(codeStop))->second;
            Stop *dest = stopsvec.at(stopNumberDEST);
            Line line1(code,name,dest,night, haversine(src,dest),Line::AUTOCARRO);
            Line *line = new Line(line1);
            graph.addEdge(stopNumberSRC,line);

            stopNumberSRC = stopNumberDEST;
            src = dest;
        }
        lineDir.close();

    }

}

InfoSTCP::InfoSTCP() {
    GetDataSet getbst("../dataset/stops.csv");

    stopsvec = getbst.getStops();
    stopsvec.insert(stopsvec.begin(),new Stop(0,"","","",0,0));

    stopMap = getbst.getMap();

    Graph g(stopsvec,stopsvec.size(),false);

    this->graph = g;

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
    std::list<int> l = graph.dijkstra_path(stopMap.find("INF1")->second,stopMap.find("DL5")->second);
    for(auto sus:l){
        if(stopsvec[sus]->getLinePred()->type == Line::START)
            std::cout << stopsvec[sus]->getCode() << " Start" <<std::endl;
        else{
            std::cout << stopsvec[sus]->getCode() << " using line: " << stopsvec[sus]->getLinePred()->getCode()<<std::endl;
        }
    }
}


