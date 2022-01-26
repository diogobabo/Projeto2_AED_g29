
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include "Line.h"
#include "Stop.h"
#include <algorithm>

using namespace std;

class Graph {
    // line é Edge(linha)
    // stop é node(bola)

    int size;               // Graph size (vertices are numbered from 1 to n)
    bool directed;        // false: undirect; true: directed
    vector<Stop *> nodes; // The list of nodes being represented

public:
    Graph();
    Graph(vector<Stop *>& vec,int size, bool dir = false);
    void addEdge(int src,Line *line);

};

#endif
