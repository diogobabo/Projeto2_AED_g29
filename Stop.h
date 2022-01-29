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

    /**
    * Constructor of the class
    * @param number: number of stop
    * @param Code: code of stop
    * @param name: name of stop
    * @param zone: zone of stop
    * @param latitude: latitude of stop
    * @param longitude: longitude of stop
    **/
    Stop(int number,std::string Code,std::string name,std::string zone,double latitude,double longitude);

    /**
   * adds a line to a the adjacent lines vector of a stop
   * @param line
   **/
   void addOutgoingLine(Line* line);

    /**
    * returns the number of the stop
    * @return num of the stop
    **/
   int getNum();

    /**
    * returns the lines' vector
    * @return vector of pointers to line
    **/
   std::vector<Line*>& getAdj();

    /**
     * sets the name of the stop
     * @param name
     **/
   void setName(std::string name);

    /**
      * sets the code of the stop
      * @param code
      **/
   void setCode(std::string code);

    /**
      * sets the zone of the stop
      * @param zone
      **/
   void setZone(std::string zone);

    /**
       * sets the latitude of the stop
       * @param lat
       **/
   void setLatitude(double lat);

    /**
       * sets the longitude of the stop
       * @param lon
       **/
   void setLongitude(double lon);

    /**
     * returns the code of the stop
     * @return code of a stop
     **/
   std::string getCode();

    /**
      * returns the code of the stop
      * @return code of a stop
      **/
   std::string getName();

    /**
      * returns the code of the stop
      * @return code of a stop
      **/
   std::string getZone();

    /**
      * returns the latitude of the stop
      * @return code latitude a stop
      **/
   double getLatitude();

    /**
      * returns the longitude of the stop
      * @return longitude of a stop
      **/
   double getLongitude();

   /**
   * overloading of operator <
   * @param s1
   * @return: a boolean
   **/
    bool operator<(const Stop &s1) const;

    /**
        * overloading of operator ==
        * @param: s1
        * @return: bool if they are equal or not
        **/
    bool operator==(const Stop &s1) const;

    /**
      * set the pred. of the stop
      * @param pred
      * @param line
      **/
    void setPred(int pred,Line* line);

    /**
      * returns the pred. of the stop
      * @return the stop before (used in dijkstra)
      **/
    int getPred();

    /**
      * returns the pred. line of the stop
      * @return the point to the line before (used in dijkstra)
      **/
    Line* getLinePred();

    bool visited;

    double dist;

};


#endif //PROJETO2_AED_STOP_H
