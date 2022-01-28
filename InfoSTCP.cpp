//
// Created by Diogo Babo on 25/01/2022.
//

#include "InfoSTCP.h"

bool InfoSTCP::isNumber(const std::string &s)            //verifies if the string contains only numbers
{
    for(int x = 0; x<s.size();x++){

        if(isdigit(s[x]) == false)
            return false;

    }
    return true;
}

void InfoSTCP::readLines(const std::string& filename) {
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
        Stop *src = stopsVec.at(stopNumberSRC);

        for(int var = 1; var<lineNumber; var++) { //aqui dentro crias as linhas
            getline(lineDir,codeStop);

            int stopNumberDEST = (stopMap.find(codeStop))->second;
            Stop *dest = stopsVec.at(stopNumberDEST);
            Line line1(code,name,dest,night, haversine(src,dest),Line::AUTOCARRO);
            Line *line = new Line(line1);
            graph.addEdge(stopNumberSRC,line);
            lineVec.push_back(line);

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
        src = stopsVec.at(stopNumberSRC);

        for(int var = 1; var<lineNumber; var++) { //aqui dentro crias as linhas
            getline(lineDir,codeStop);

            int stopNumberDEST = (stopMap.find(codeStop))->second;
            Stop *dest = stopsVec.at(stopNumberDEST);
            Line line1(code,name,dest,night, haversine(src,dest),Line::AUTOCARRO);
            Line *line = new Line(line1);
            graph.addEdge(stopNumberSRC,line);
            lineVec.push_back(line);

            stopNumberSRC = stopNumberDEST;
            src = dest;
        }
        lineDir.close();

    }

}

InfoSTCP::InfoSTCP() {
    maxWalkingDistance = 0;
    GetDataSet getbst("../dataset/stops.csv");

    stopsVec = getbst.getStops();
    stopsVec.insert(stopsVec.begin(),new Stop(0,"","","",0,0));
    stopMap = getbst.getMap();
    Graph g(stopsVec,stopsVec.size(),false);
    this->graph = g;

    readLines("../dataset/lines.csv");
    setNewWalkDistance(0.1);

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
    functionTest();
    std::list<int> l = graph.dijkstra_path(stopMap.find("PDC")->second,stopMap.find("MAKR4")->second);

    for(auto sus:l){
        if(stopsVec[sus]->getLinePred()->type == Line::START)
            std::cout << stopsVec[sus]->getCode() << " " << stopsVec[sus]->getName() << " Start" <<std::endl;
        else{
            std::cout << stopsVec[sus]->getCode() << " " << stopsVec[sus]->getName() << " using line: " << stopsVec[sus]->getLinePred()->getCode()<<std::endl;
        }
    }
}

void InfoSTCP::addStop(std::string code, std::string name, std::string zone, long lat, long lon) {
    int number;
    number = stopMap.size() + 1;
    Stop stop1(number,code,name,zone,lat,lon);
    Stop * stop = new Stop(stop1);
    pair<std::string,int> stopPair(code,number);
    stopMap.insert(stopPair);
    stopsVec.push_back(stop);

}

void InfoSTCP::functionTest() {
    for(auto sus:lineVec){
        if(sus->getNight())sus->null=true;
        else if(sus->getType() != Line::AUTOCARRO)sus->null=true;
    }
}

void InfoSTCP::setNewWalkDistance(double newWalkingDistance) {
    if(newWalkingDistance < 0){
        return;
    }
    else if(newWalkingDistance == maxWalkingDistance){
        return;
    }
    else if(newWalkingDistance<maxWalkingDistance){
        this->maxWalkingDistance = newWalkingDistance;
        reduceArtificialLineVec();
    }else{
        double d = maxWalkingDistance;
        this->maxWalkingDistance = newWalkingDistance;
        enlargeArtificialLineVec(d);
    }
}

void InfoSTCP::reduceArtificialLineVec() {
    for(auto l : artificialLineVec){
        if(l->getDistance() > maxWalkingDistance){
            l->null = true;
        }
    }
}

void InfoSTCP::enlargeArtificialLineVec(double lastWalkingDistance) {
    int l = 0;
    double o = 0,p = 0,f = -1;

    for(auto l : artificialLineVec) {
        if(l->getDistance() <= maxWalkingDistance){
            l->null = false;
        }
    }

    for(auto stops1 : stopsVec){

        if(o == 0){o = 1;continue;}

        for(auto stops2 : stopsVec){
            if(l== 0){l = 1;continue;}
            if(stops1 != stops2){
                double distance = haversine(stops1,stops2);
                if(lastWalkingDistance < distance && distance <= maxWalkingDistance){

                    Line l1(stops1->getCode(),"Walk to: "+stops1->getName()+" Stop", stops1,false,distance,Line::WALKING);
                    Line *l11 = new Line(l1);
                    stops2->addOutgoingLine(l11);
                    artificialLineVec.push_back(l11);

                    Line l2(stops2->getCode(),"Walk to: "+stops2->getName()+" Stop", stops2,false,distance,Line::WALKING);
                    Line *l21 = new Line(l2);
                    stops1->addOutgoingLine(l21);
                    artificialLineVec.push_back(l21);
                }
            }

        }

        p = o / stopsVec.size();

        if( p > f +0.16){
            f = p;
            showStatusBar(p);
        }

        o = o + 1;
    }
}

void InfoSTCP::showMenu() {
    std::cout << " ____________________________________________________________________________________" <<  std::endl;
    std::cout << "|                                                                                   |" <<  std::endl;
    std::cout << "|                                                                                   |" <<  std::endl;
    std::cout << "|                                                         __|__                     |" <<  std::endl;
    std::cout << "|    *OPTIONS*                                     --------(_)--------              |" <<  std::endl;
    std::cout << "|                                                    O  O       O  O                |" <<  std::endl;
    std::cout << "|    0 -> EXIT                                                                      |" <<  std::endl;
    std::cout << "|    1 -> SEARCH                                                                    |" <<  std::endl;
    std::cout << "|    2 -> SETTINGS                                                                  |" <<  std::endl;
    std::cout << "|                                                                                   |" <<  std::endl;
    std::cout << " ------------------------------------------------------------------------------------" <<  std::endl;
}

void InfoSTCP::menu() {
    bool flag = true;

    int number = 50;

    while (flag) {          //checks the input
        showMenu();

        std::string x;

        std::cin >> x;

        if (std::cin.fail() || std::cin.peek() != '\n' || x.size() != 1 || !isNumber(x)) {
            std::system(CLEAR);
            std::cout << "Invalid input, please try again: " << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();

            flag = true;

        } else {

            std::stringstream ss(x);

            ss >> number;

            if (number == 1 || number == 2 || number == 0) {
                flag = false;
            } else {
                std::system(CLEAR);
                std::cout << "Invalid input, please try again:" << std::endl;
            }
        }
        if (flag == false) {
            if (number == 0) {
                return;
            } else if (number == 1) {
                flag = true;
            } else if (number == 2) {
                flag = true;
            }
        }
    }
}

void InfoSTCP::showStatusBar(double progress) {

        int barWidth = 70;

        std::cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();

    std::cout << std::endl;
}