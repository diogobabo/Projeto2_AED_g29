
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include "Line.h"
#include "Stop.h"
#include <algorithm>
#include "MinHeap.h"

#define INF (INT_MAX/2)

class Graph {
    // line é Edge(linha)
    // stop é node(bola)

    int size;               // Graph size (vertices are numbered from 1 to n)
    bool directed;        // false: undirect; true: directed
    std::vector<Stop *> nodes; // The list of nodes being represented

public:
    Graph();
    Graph(std::vector<Stop *>& vec,int size, bool dir = false);
    void addEdge(int src,Line *line);
    std::list<int> dijkstra_path(int a, int b);
    void dijkstra(int s);
    void bfs(int v);
    void addNode(Stop *stop1);
    std::list<int> bfs_path(int a, int b);
};

#endif
