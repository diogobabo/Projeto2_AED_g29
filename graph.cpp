
#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)

Graph::Graph(std::vector<Stop *> &vec, int size, bool dir):nodes(vec),size(size),directed(dir) {
}

// Add edge from source to destination with a certain weight

void Graph::addEdge(int src,Line *line) {
    if (line->getDest()->getNum() <1 || line->getDest()->getNum() >size) return;
    nodes[src]->getAdj().push_back(line);
}

Graph::Graph() {

}

std::list<int> Graph::dijkstra_path(int a, int b) {
    dijkstra(a);
    list<int> path;
    if (nodes[b]->dist == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v]->pred;
        path.push_front(v);
    }
    return path;
}

void Graph::dijkstra(int s) {
    MinHeap<int, int> q(size, -1);
    for (int v=1; v<size; v++) {
        nodes[v]->dist = INF;
        q.insert(v, INF);
        nodes[v]->visited = false;
    }
    nodes[s]->dist = 0;
    q.decreaseKey(s, 0);
    nodes[s]->pred = s;
    while (q.getSize()>0) {
        int u = q.removeMin();
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u]->visited = true;
        for (auto e : nodes[u]->getAdj()) {
            int v = e->getDest()->getNum();
            int w = e->weight;
            if (!nodes[v]->visited && nodes[u]->dist + w < nodes[v]->dist) {
                nodes[v]->dist = nodes[u]->dist + w;
                q.decreaseKey(v, nodes[v]->dist);
                nodes[v]->pred = u;
            }
        }
    }
}


