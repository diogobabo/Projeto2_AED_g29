
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include "Line.h"
#include "Stop.h"
#include <algorithm>
#include "MinHeap.h"
#include <queue>
#include <map>

#define INF (INT_MAX/2)

class Graph {
    // line é Edge
    // stop é node

    int size;               // Graph size (vertices are numbered from 1 to n)
    bool directed;        // false: undirect; true: directed
    std::vector<Stop *> nodes; // The list of nodes being represented

public:
    /**
    * Default Constructor of the class
    **/
    Graph();

    /**
    * Constructor of the class
    * @param vec: node vector
    * @param size: size
    * @param dir: directed
    **/
    Graph(std::vector<Stop *>& vec,int size, bool dir = false);

    /**
   * adds a edge to the graph
    * @param src : starting node
     * @param line: the line
   **/
    void addEdge(int src,Line *line);

    std::list<int> dijkstra_path(int a, int b);
    std::list<int> bfs_path(int a, int b);
    std::list<int> dijkstra_cheap_path(int a, int b);
    std::list<int> dijkstra_bus_path(int a, int b);

    /**
    * dijkstra
     * @TimeComplexity: O(N_LINES * LOG(N_NODES))
     * @param s : starting node
    **/
    void dijkstra(int s);

    /**
   * dijkstra
    * @TimeComplexity: O(N_LINES * LOG(N_NODES))
    * @param s : starting node
   **/
    void dijkstra_Cheap(int s);

    /**
   * dijkstra
    * @TimeComplexity: O(N_LINES * LOG(N_NODES))
    * @param s : starting node
   **/
    void dijkstra_bus(int s);

    /**
   * bfs
    * @TimeComplexity: O(N_LINES^2)
    * @param v : starting node
   **/
    void bfs(int v);

    /**
   * adds a stop(node) to the graph
    * @param stop1
   **/
    void addNode(Stop *stop1);
};

#endif
