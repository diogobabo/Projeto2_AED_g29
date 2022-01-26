
#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)

Graph::Graph(vector<Stop *> &vec, int size, bool dir):nodes(vec),size(size),directed(dir) {
}

// Add edge from source to destination with a certain weight

void Graph::addEdge(int src,Line *line) {
    if (line->getDest()->getNum() <1 || line->getDest()->getNum() >size) return;
    nodes[src]->getAdj().push_back(line);
}

Graph::Graph() {

}


