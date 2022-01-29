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
#include <cmath>
#include "GetDataSet.h"
#include "graph.h"
#include <iostream>

class InfoSTCP {
private:
    list <Stop*> searchByName();
    Stop* searchByCode();
    Stop* searchByCoordinates();
    static bool isNumber(const std::string &s);
    std::vector<Stop *> stopsVec;
    std::vector<Line *> lineVec;
    std::vector<Line *> artificialLineVec;
    static double haversine(Stop* stop1,Stop* stop2);
    std::map<std::string,int> stopMap;
    Graph graph;
    double maxWalkingDistance;
    void functionTest();
    void reduceArtificialLineVec();
    void enlargeArtificialLineVec(double lastWalkingDistance);
    void showMenu();
    void start();
    void showStatusBar(double progress);
    void settings();
    void applyMeans();
    void lessStops();
    void lessDistance();
    bool inArtificialLineVec(Stop *s1,Stop *s2);
    Stop* originMenu();
    Stop* destinyMenu();
    bool bus,eletric,walking,noturno;
public:
    InfoSTCP();
    void setNewWalkDistance(double newWalkingDistance);
    void readLines(const std::string& filename);
    void addStop(std::string code, std::string name, std::string zone, long lat, long lon);
    void addLine();
    void checkInput();
    void walkingDistance();
    void menu();
    bool isDouble(std::string num);
    void meansTransport();
};


#endif //PROJETO2_AED_INFOSTCP_H
