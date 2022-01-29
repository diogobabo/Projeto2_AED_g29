#ifndef PROJETO2_AED_LINE_H
#define PROJETO2_AED_LINE_H


#include <string>

class Stop;

class Line {
private:
    std::string name;
    std::string code;
    Stop *dest;
    bool atNight;
    double distance;
public:
    enum TYPE{
        AUTOCARRO,
        ELETRICO,
        WALKING,
        START
    };
    bool null;
    TYPE type;
    /**
    * Constructor of the class
    * @param code: code of stop
    * @param name: name of stop
    * @param dest: destination stop
    * @param atNight: night time line
    * @param distance: distance between both stops
     * @param type: type of line
    **/
    Line(std::string code,std::string name,Stop *dest,bool atNight,double distance,TYPE type);

    /**
    * Constructor of the class
     * @param type: type of line
    **/
    Line(TYPE type);

    /**
     * sets the name of the line
     * @param name
     **/
    void setName(std::string name);

    /**
      * sets the code of the stop
      * @param code
      **/
    void setCode(std::string code);

    /**
      * sets the destination stop
      * @param dest
      **/
    void setDest(Stop *dest);

    /**
      * sets the line as night time one
      **/
    void setNight();

    /**
      * sets the type of the line
      * @param type
      **/
    void setType(TYPE type);

    /**
      * sets the distance
      * @param distance
      **/
    void setDistance(double distance);

    /**
     * returns the name of the line
     * @return line name
     **/
    std::string getName();

    /**
     * returns the code of the line
     * @return line code
     **/
    std::string getCode();

    /**
     * returns the destination stop
     * @return pointer to that stop
     **/
    Stop* getDest();

    /**
     * returns a bool if the line is NIGHT / DAY
     * @return boolean
     **/
    bool getNight();

    /**
     * returns type of the line
     * @return line type
     **/
    TYPE getType();

    /**
     * returns the distance between 2 stops
     * @return line distance
     **/
    double getDistance();

    /**
      * sets the weight of the line
      * @param weight
      **/
    void setWeight(double weight);

    double weight;
};


#endif //PROJETO2_AED_LINE_H
