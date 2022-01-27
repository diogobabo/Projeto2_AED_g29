//
// Created by Diogo Babo on 18/01/2022.
//

#ifndef PROJETO2_AED_STOP_H
#define PROJETO2_AED_STOP_H


#include <string>
#include <vector>

class Line;

class Stop {
private:
    int number;
    std::string code,name,zone;
    double latitude,longitude;
    std::vector<Line*> adj;
    Line* lineUsedToArrive;
    int pred;
public:
    Stop(int number,std::string Code,std::string name,std::string zone,double latitude,double longitude);
    void addOutgoingLine(Line* line);
    int getNum();
    std::vector<Line*>& getAdj();
    void setName(std::string name);
    void setCode(std::string code);
    void setZone(std::string zone);
    void setLatitude(double lat);
    void setLongitude(double lon);
    std::string getCode();
    std::string getName();
    std::string getZone();
    double getLatitude();
    double getLongitude();
    bool operator<(const Stop *s1) const;
    bool operator==(const Stop *s1) const;
    void setPred(int pred,Line* line);
    int getPred();
    Line* getLinePred();
    bool visited;
    int dist;

};


#endif //PROJETO2_AED_STOP_H
