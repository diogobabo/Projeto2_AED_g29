
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include "Line.h"
#include "Stop.h"

using namespace std;

class Graph {
    Line line;// Edge(linha)


    Stop stop;// node(bola)
    int size;               // Graph size (vertices are numbered from 1 to n)
    bool directed;        // false: undirect; true: directed
    vector<Stop> stops; // The list of nodes being represented

public:

    Graph(int nodes, bool dir = false);

    void addEdge(int src, int dest, int weight = 1);

};

#endif
