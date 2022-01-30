
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
    bus = true;
    eletric = true;
    walking = false;
    noturno = false;
    leastStops = true;
    leastDistance = false;
    cheapest = false;
    leastWalking = false;
    readLines("../dataset/lines.csv");
    applyMeans();

}
double InfoSTCP::haversine(Stop* stop1,Stop* stop2)
{
    //double M_PI = 3.14159265358979323846;
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

void InfoSTCP::addStop(std::string code, std::string name, std::string zone, long lat, long lon) {
    int number;
    number = stopMap.size() + 1;
    Stop stop1(number,code,name,zone,lat,lon);
    Stop * stop = new Stop(stop1);
    pair<std::string,int> stopPair(code,number);
    stopMap.insert(stopPair);
    stopsVec.push_back(stop);
    graph.addNode(stop);

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
        if(l->getDistance() <= maxWalkingDistance && l->getType() == Line::WALKING){
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
                    Line l1(stops2->getCode(),"Walk to: "+stops1->getName()+" Stop", stops1,false,distance,Line::WALKING);
                    Line *l11 = new Line(l1);
                    stops2->addOutgoingLine(l11);
                    artificialLineVec.push_back(l11);

                    Line l2(stops1->getCode(),"Walk to: "+stops2->getName()+" Stop", stops2,false,distance,Line::WALKING);
                    Line *l21 = new Line(l2);
                    stops1->addOutgoingLine(l21);
                    artificialLineVec.push_back(l21);
                }
            }

        }

        p = o / stopsVec.size();
        if( p > f +0.16){f = p;showStatusBar(p);}
        o = o + 1;
    }
}

void InfoSTCP::showMenu() {
    std::cout << " ____________________________________________________________________________________" <<  std::endl;
    std::cout << "|                                                                                   |" <<  std::endl;
    std::cout << "|                                                                                   |" <<  std::endl;
    std::cout << "|                                                     _____________                 |" <<  std::endl;
    std::cout << "|                                                   _/_|[][][][][] | - -            |" <<  std::endl;
    std::cout << "|    *OPTIONS*                                     (      City Bus | - -            |" <<  std::endl;
    std::cout << "|                                                   =--OO-------OO--=dwb            |" <<  std::endl;
    std::cout << "|    0 -> EXIT                                                                      |" <<  std::endl;
    std::cout << "|    1 -> STANDARD SEARCH                                                           |" <<  std::endl;
    std::cout << "|    2 -> SETTINGS                                                                  |" <<  std::endl;
    std::cout << "|    3 -> NON-STANDARD MENU                                                         |" <<  std::endl;
    std::cout << "|                                                                                   |" <<  std::endl;
    std::cout << " ------------------------------------------------------------------------------------" <<  std::endl;
}

void InfoSTCP::menu() {
    bool flag = true;

    int number = 50;

    while (flag) {//checks the input
        showMenu();

        std::string x;

        std::cin >> x;

        if (std::cin.fail() || std::cin.peek() != '\n' || x.size() != 1 || !isNumber(x)) {
            std::cout << "Invalid input, please try again: " << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();

            flag = true;

        } else {

            std::stringstream ss(x);

            ss >> number;

            if (number == 1 || number == 2 || number == 0|| number == 3) {
                flag = false;
            } else {
                std::cout << "Invalid input, please try again:" << std::endl;
            }
        }
        if (flag == false) {
            if (number == 0) {
                return;
            } else if (number == 1) {
                flag = true;
                Stop *s1,*s2;
                s1 = originMenu();
                if(s1 == nullptr){
                    continue;
                }
                s2 = destinyMenu();
                if(s2 == nullptr){
                    continue;
                }
                printBestPath(s1,s2);
            } else if (number == 2) {
                settings();
                flag = true;
            }else if (number == 3) {
                nonStandard();
                flag = true;
            }
        }
    }
}

void InfoSTCP::nonStandard() {
    bool flag = true;

    int number = 50;

    while (flag) {//checks the input

        std::cout << "1) Search without starting station" << std::endl;
        std::cout << "2) Add Line" << std::endl;
        std::cout << "3) Add Stop" << std::endl;
        std::cout << "3) Show Near Stations" << std::endl;
        std::cout << "0) Exit" << std::endl;

        std::string x;

        std::cin >> x;

        if (std::cin.fail() || std::cin.peek() != '\n' || x.size() != 1 || !isNumber(x)) {
            std::cout << "Invalid input, please try again: " << std::endl;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.clear();

            flag = true;

        } else {

            std::stringstream ss(x);

            ss >> number;

            if (number == 1 || number == 2 || number == 0|| number == 3) {
                flag = false;
            } else {
                std::cout << "Invalid input, please try again:" << std::endl;
            }
        }
        if (flag == false) {
            if (number == 0) {
                return;
            } else if (number == 1) {
                pathWithoutLocation();
            } else if (number == 2) {
                settings();
                flag = true;
            }else if (number == 3) {
                settings();
                flag = true;
            }
        }
    }
}
void InfoSTCP::pathWithoutLocation(){

}
void InfoSTCP::printBestPath(Stop *s1, Stop *s2) {
    resetWeight();
    std::list<int> l;

    if(leastStops){
        l = graph.bfs_path(stopMap.find(s1->getCode())->second,stopMap.find(s2->getCode())->second);
    }
    else if(leastDistance){
        lessDistance();
        l = graph.dijkstra_path(stopMap.find(s1->getCode())->second,stopMap.find(s2->getCode())->second);
    }
    else if(cheapest){
        l = graph.dijkstra_cheap_path(stopMap.find(s1->getCode())->second,stopMap.find(s2->getCode())->second);
    }
    else if(leastWalking){
        leastWalkingLines();
        l = graph.dijkstra_path(stopMap.find(s1->getCode())->second,stopMap.find(s2->getCode())->second);
    }

    if(l.empty()){
        std::cout << " There is no viable Path with the current settings" <<std::endl;
    }

    for(auto sus:l){
        if(stopsVec[sus]->getLinePred()->type == Line::START)
            std::cout << stopsVec[sus]->getCode() << " " << stopsVec[sus]->getName() << " Start" <<std::endl;
        else if(stopsVec[sus]->getLinePred()->type == Line::WALKING)
            std::cout << "From here: " <<stopsVec[sus]->getLinePred()->getCode() << " Walk " << stopsVec[sus]->getLinePred()->getDistance()<< " km to " << stopsVec[sus]->getName()+" "+ stopsVec[sus]->getCode()  << " " <<std::endl;
        else{
            std::cout << "Get here - " <<stopsVec[sus]->getCode() << " also known as -" << stopsVec[sus]->getName() << " By using line - " << stopsVec[sus]->getLinePred()->getCode()<< " " + stopsVec[sus]->getZone()<<std::endl;
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

void InfoSTCP::settings() {
    bool flag = true;

    int number = 50;

    while (flag) {
        std::string x;

        std::cout << "1) Walking Distance" << std::endl;
        std::cout << "2) Means of Transport e Horario" << std::endl;
        std::cout << "3) Best path" << std::endl;
        std::cout << "0) Exit" << std::endl;

        cin >> x;

        if(std::cin.fail() || std::cin.peek() != '\n' || x.size() != 1 || !isNumber(x)) {
            std::cout << "Invalid input, please try again: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cin.clear();
            flag = true;
        }else {
            std::stringstream ss(x);

            ss >> number;
            if (number == 1 || number == 2 || number == 0 || number == 3) {
                flag = false;
            }
            else {
                std::cout << "Invalid input, please try again:" << std::endl;
                flag = true;
            }
        }
        if (flag == false) {
            if (number == 0) {
                return;
            } else if (number == 1) {
                walkingDistance();
                flag = true;
            } else if (number == 2) {
                meansTransport();
                flag = true;
            }else if(number == 3){
                bestPath();
                flag = true;
            }
        }
    }
}

void InfoSTCP::walkingDistance() {
    bool flag = true;

    int number = 50;

    while (flag) {
        std::string x;

        std::string andar = walking ? "ON AND SET TO: " + to_string(maxWalkingDistance) + " KM" : "OFF";
        std::cout << "1) Walking -> " << andar << std::endl;
        std::cout << "0) Exit" << std::endl;

        cin >> x;

        if(std::cin.fail() || std::cin.peek() != '\n' || x.size() != 1 || !isNumber(x)) {
            std::cout << "Invalid input, please try again: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cin.clear();
            flag = true;
        }else {
            std::stringstream ss(x);

            ss >> number;
            if (number == 1 || number == 0) {
                flag = false;
            }
            else {
                std::cout << "Invalid input, please try again:" << std::endl;
                flag = true;
            }
        }
        if (flag == false) {
            if (number == 0) {
                return;
            } else if (number == 1) {
                std::string km;
                std::cout << "Set the distance you are willing to walk! (km)" << std::endl;
                cin >> km;
                while (std::cin.fail() || std::cin.peek() != '\n' || !isDouble(km)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input, please try again: " << std::endl;
                    cin >> km;
                }
                double dis = std::stod(km);
                setNewWalkDistance(dis);
                if(dis == 0.0){
                    walking = false;
                }
                else{
                    walking = true;
                }
                flag = true;
            }
        }
    }
}

bool InfoSTCP::isDouble(std::string num) {
    bool isDD = true;
    int counter = 0;
    for(int i = 0; i < num.length(); i++) {
        if(num[i] == '.') {
            counter++;
            continue;
        }
        if(isdigit(num[i]) == false) {
            isDD = false;
        }
    }
    if(counter <= 1 && isDD) {
        return true;
    }
    return false;
}

void InfoSTCP::meansTransport() {
    bool flag = true;

    int number = 50;

    while (flag) {
        std::string x;

        std::string autocarro = bus ? "ON" : "OFF";
        std::string eletrico = eletric ? "ON" : "OFF";
        std::string n = noturno ? "ON" : "OFF";
        std::cout << "1) Bus -> " << autocarro  << std::endl;
        std::cout << "2) Eletric -> " << eletrico << std::endl;
        std::cout << "3) Periodo Noturno -> " << n << std::endl;
        std::cout << "0) Exit" << std::endl;

        cin >> x;

        if(std::cin.fail() || std::cin.peek() != '\n' || x.size() != 1 || !isNumber(x)) {
            std::cout << "Invalid input, please try again: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cin.clear();
            flag = true;
        }else {
            std::stringstream ss(x);

            ss >> number;
            if (number == 1 || number == 2 || number == 0 || number == 3) {
                flag = false;
            }
            else {
                std::cout << "Invalid input, please try again:" << std::endl;
                flag = true;
            }
        }
        if (flag == false) {
            if (number == 0) {
                applyMeans();
                return;
            } else if (number == 1) {
                bus ? bus = false : bus = true;
                flag = true;
            } else if (number == 2) {
                eletric ? eletric = false : eletric = true;
                flag = true;
            }else if(number == 3){
                noturno ? noturno = false : noturno = true;
                flag = true;
            }
        }
    }
}

void InfoSTCP::applyMeans() {
    for(auto l : lineVec){
        if(l->getType() == Line::AUTOCARRO){
            if(this->bus){
                l->null = false;
            }else{
                l->null = true;
            }
        }
        else if(l->getType() == Line::ELETRICO){
            if(this->eletric){
                l->null = false;
            }else{
                l->null = true;
            }
        }
        if(l->getNight() && !noturno){
            l->null = true;
        }
        else if(!l->getNight() && noturno){
            l->null = true;
        }
    }
}

list <Stop*> InfoSTCP::searchByName() {
    std::string name;
    std::cout << "Type the Name Of The Stop!" << std::endl;
    cin >> name;
    list <Stop*> temp;
    for(auto it = stopsVec.begin(); it != stopsVec.end(); it++) {
        if((*it)->getName() == name) {
            temp.push_back(*it);
        }
    }
    return temp;
}

Stop* InfoSTCP::searchByCode() {
    std::string code;
    std::cout << "Type the Code Of The Stop!" << std::endl;
    cin >> code;
    auto it = stopMap.find(code);
    if(it != stopMap.end()) {
        return stopsVec[it->second];
    }
    return nullptr;
}

Stop* InfoSTCP::searchByCoordinates() {
    std::string lon,lat;
    std::cout << "Type the Latitude Of The Stop!" << std::endl;
    cin >> lat;
    while (std::cin.fail() || std::cin.peek() != '\n' || !isDouble(lat)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, please try again: " << std::endl;
        cin >> lat;
    }
    double latitude = std::stod(lat);
    std::cout << "Type the Longitude Of The Stop!" << std::endl;
    cin >> lon;
    while (std::cin.fail() || std::cin.peek() != '\n' || !isDouble(lon)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input, please try again: " << std::endl;
        cin >> lon;
    }
    double longitude = std::stod(lon);
    for(auto it = stopsVec.begin(); it != stopsVec.end(); it++) {
        if((*it)->getLatitude() == latitude && (*it)->getLongitude() == longitude) {
            return *it;
        }
    }
    return nullptr;
}


Stop* InfoSTCP::originMenu() {
    bool flag = true;

    int number = 50;

    while (flag) {
        std::string x;

        std::cout << "How would you rather give the info of Origin Stop:" <<  std::endl;
        std::cout << "1) By Code" << std::endl;
        std::cout << "2) By Name" << std::endl;
        std::cout << "3) By Coordinates" << std::endl;
        std::cout << "0) Exit" << std::endl;

        cin >> x;

        if(std::cin.fail() || std::cin.peek() != '\n' || x.size() != 1 || !isNumber(x)) {
            std::cout << "Invalid input, please try again: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cin.clear();
            flag = true;
        }else {
            std::stringstream ss(x);

            ss >> number;
            if (number == 1 || number == 2 || number == 0 || number == 3) {
                flag = false;
            }
            else {
                std::cout << "Invalid input, please try again:" << std::endl;
                flag = true;
            }
        }
        if (flag == false) {
            if (number == 0) {
                return nullptr;
            } else if (number == 1) {
                flag = true;
                Stop* s1 = searchByCode();
                if(s1 == nullptr) {
                    std::cout << "Couldn't find the stop wanted, try again!" << std::endl;
                }
                else {
                    return s1;
                }
            } else if (number == 2) {
                list <Stop*> temp = searchByName();
                if(temp.size() == 1) {
                    return temp.front();
                }
                else if(temp.size() == 0) {
                    std::cout << "Couldn't find the stop wanted, try again!" << std::endl;
                }
                else {
                    cout << "Code : Latitude : Longitude" << std::endl;
                    for(auto x : temp) {
                        cout << x->getCode() << " : " << x->getLatitude() << " : " << x->getLongitude() << std::endl;
                    }
                }
                flag = true;
            }else if(number == 3){
                flag = true;
                Stop* s1 = searchByCoordinates();
                if(s1 == nullptr) {
                    std::cout << "Couldn't find the stop wanted, try again!" << std::endl;
                }
                else {
                    return s1;
                }
            }
        }
    }
    return nullptr;
}

Stop* InfoSTCP::destinyMenu() {
    bool flag = true;

    int number = 50;

    while (flag) {
        std::string x;

        std::cout << "How would you rather give the info of Destiny Stop:" <<  std::endl;
        std::cout << "1) By Code" << std::endl;
        std::cout << "2) By Name" << std::endl;
        std::cout << "3) By Coordinates" << std::endl;
        std::cout << "0) Exit" << std::endl;

        cin >> x;

        if(std::cin.fail() || std::cin.peek() != '\n' || x.size() != 1 || !isNumber(x)) {
            std::cout << "Invalid input, please try again: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cin.clear();
            flag = true;
        }else {
            std::stringstream ss(x);

            ss >> number;
            if (number == 1 || number == 2 || number == 0 || number == 3) {
                flag = false;
            }
            else {
                std::cout << "Invalid input, please try again:" << std::endl;
                flag = true;
            }
        }
        if (flag == false) {
            if (number == 0) {
                return nullptr;
            } else if (number == 1) {
                flag = true;
                Stop* s1 = searchByCode();
                if(s1 == nullptr) {
                    std::cout << "Couldn't find the stop wanted, try again!" << std::endl;
                }
                else {
                    return s1;
                }
            } else if (number == 2) {
                list <Stop*> temp = searchByName();
                if(temp.size() == 1) {
                    return temp.front();
                }
                else if(temp.size() == 0) {
                    std::cout << "Couldn't find the stop wanted, try again!" << std::endl;
                }
                else {
                    cout << "Code : Latitude : Longitude" << std::endl;
                    for(auto x : temp) {
                        cout << x->getCode() << " : " << x->getLatitude() << " : " << x->getLongitude() << std::endl;
                    }
                }
                flag = true;
            }else if(number == 3){
                flag = true;
                Stop* s1 = searchByCoordinates();
                if(s1 == nullptr) {
                    std::cout << "Couldn't find the stop wanted, try again!" << std::endl;
                }
                else {
                    return s1;
                }
            }
        }
    }
    return nullptr;
}

void InfoSTCP::lessStops() {
    for(auto it = lineVec.begin(); it != lineVec.end(); it++) {
        (*it)->setWeight(0.0);
    }
}

void InfoSTCP::lessDistance() {
    for(auto it = lineVec.begin(); it != lineVec.end(); it++) {
        (*it)->setWeight((*it)->getDistance());
    }
    for(auto it = artificialLineVec.begin(); it != artificialLineVec.end(); it++) {
        (*it)->setWeight((*it)->getDistance());
    }
}

void InfoSTCP::bestPath() {
    bool flag = true;

    int number = 50;

    while (flag) {
        std::string x;
        std::string lStops = leastStops ? "ON" : "OFF";
        std::string lDistance = leastDistance ? "ON" : "OFF";
        std::string lPrice = cheapest ? "ON" : "OFF";
        std::string lWalking = leastWalking ? "ON" : "OFF";
        std::cout << "1) Least Stops -> " << lStops << std::endl;
        std::cout << "2) Least Distance -> " << lDistance << std::endl;
        std::cout << "3) Least Price -> " << lPrice << std::endl;
        std::cout << "4) Least Walking -> " << lWalking << std::endl;
        std::cout << "0) Exit" << std::endl;

        cin >> x;

        if(std::cin.fail() || std::cin.peek() != '\n' || x.size() != 1 || !isNumber(x)) {
            std::cout << "Invalid input, please try again: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cin.clear();
            flag = true;
        }else {
            std::stringstream ss(x);

            ss >> number;
            if (number == 1 || number == 2 || number == 0 || number == 3 || number == 4) {
                flag = false;
            }
            else {
                std::cout << "Invalid input, please try again:" << std::endl;
                flag = true;
            }
        }
        if (flag == false) {
            if (number == 0) {
                return;
            } else if (number == 1) {
                leastStops = true;
                leastDistance = false;
                cheapest = false;
                leastWalking = false;
                flag = true;
            } else if (number == 2) {
                leastDistance = true;
                leastStops = false;
                cheapest = false;
                leastWalking = false;
                flag = true;
            }else if(number == 3){
                cheapest = true;
                leastStops = false;
                leastDistance = false;
                leastWalking = false;
                flag = true;
            }else if(number == 4) {
                leastWalking = true;
                leastStops = false;
                leastDistance = false;
                cheapest = false;
                flag = true;
            }
        }
    }
}

void InfoSTCP::resetWeight() {
    for(auto it = lineVec.begin(); it != lineVec.end(); it++) {
        (*it)->setWeight(0);
    }
    for(auto it = artificialLineVec.begin(); it != artificialLineVec.end(); it++) {
        (*it)->setWeight(0);
    }
}

void InfoSTCP::leastWalkingLines() {
    for(auto it = lineVec.begin(); it != lineVec.end(); it++) {
        (*it)->setWeight(0.02);
    }
    for(auto it = artificialLineVec.begin(); it != artificialLineVec.end(); it++) {
        (*it)->setWeight((*it)->getDistance());
    }
}
