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
    /**
    * returns a list of pointers to stops with a certain name
    * @returns a list of pointers to stops
     * @TimeComplexity : O(N)
    */
    list <Stop*> searchByName();

    /**
    * returns a pointers to a stop with a certain code
    * @returns a pointer to a stop
    */
    Stop* searchByCode();

    /**
    * returns a pointers to a stop with certain coordinates
    * @returns a pointer to a stop
    */
    Stop* searchByCoordinates();

    /**
        * checks if a string is a number
        * @param s(given string)
        * @return if s is a number or not
        * @TimeComplexity : O(N)
     **/
    static bool isNumber(const std::string &s);

    std::vector<Stop *> stopsVec;

    std::vector<Line *> lineVec;

    std::vector<Line *> artificialLineVec;

    /**
        * returns a distance
        * @param stop1
        * @param stop2
        * @return distance between two stops
     **/
    static double haversine(Stop* stop1,Stop* stop2);

    std::map<std::string,int> stopMap;

    Graph graph;

    double maxWalkingDistance;

    /**
        * gives null value to the walking lines which distance is greater than the max. walking distance
     **/
    void reduceArtificialLineVec();

    /**
        * resets the weight of the edges(0)
        * @TimeComplexity : O(N)
     **/
    void resetWeight();

    /**
        * creates new walking lines depending on the lastwalking distance
        * @TimeComplexity : O(N^2)
        * @param lastWalkingDistance
     **/
    void enlargeArtificialLineVec(double lastWalkingDistance);

    /**
        * displays the menu
     **/
    void showMenu();

    /**
        * displays the loading bar
        * @param progress
     **/
    void showStatusBar(double progress);

    /**
        * displays the settings
     **/
    void settings();

    /**
        * applies the transport specifications
        * @TimeComplexity : O(N)
     **/
    void applyMeans();

    void lessStops();

    void lessDistance();

    /**
        * returns the stop of origin the user is looking for, if it doesn't exist returns nullptr
        * @return pointer to a stop
     **/
    Stop* originMenu();

    /**
        * returns the stop of destiny the user is looking for, if it doesn't exist returns nullptr
        * @return pointer to a stop
     **/
    Stop* destinyMenu();

    /**
        * prints the best path between two stops
        * @param s2
        * @param s1
     **/
    void printBestPath(Stop *s1,Stop *s2);

    /**
        * shows the menu of bestpath settings
     **/
    void bestPath();

    bool bus,eletric,walking,noturno;

    bool leastStops,leastDistance,leastWalking,cheapest,leastBusChange;

public:
    /**
    * Constructor of the class
    **/
    InfoSTCP();

    /**
       * sets the new walking distance
       * @param newWalkingDistance
    **/

    void setNewWalkDistance(double newWalkingDistance);

    /**
       * reads all the files related to lines
       * @param filename
    **/
    void readLines(const std::string& filename);

    /**
       * adds a stop
       * @param code
       * @param name
       * @param zone
       * @param lat
       * @param lon
    **/
    void addStop(std::string code, std::string name, std::string zone, long lat, long lon);

    void addLine();

    void checkInput();

    /**
        * shows the menu of means of transport settings
     **/
    void walkingDistance();

    /**
        * shows the menu
     **/
    void menu();

    /**
        * checks if a string is a double
        * @param num(given string)
        * @return if s is a double or not
     **/

    bool isDouble(std::string num);

    /**
        * shows the menu of means of transport settings
     **/
    void meansTransport();
};


#endif //PROJETO2_AED_INFOSTCP_H
