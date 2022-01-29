

#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)

Graph::Graph(std::vector<Stop *> &vec, int size, bool dir):size(size),directed(dir) {
    this->nodes = vec;
}

// Add edge from source to destination

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
        v = nodes[v]->getPred();
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
    nodes[s]->setPred(s,new Line(Line::START)) ;
    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u]->visited = true;
        for (auto e : nodes[u]->getAdj()) {
            if(e->null)continue;
            int v = e->getDest()->getNum();
            double w = e->weight;
            if (!nodes[v]->visited && nodes[u]->dist + w < nodes[v]->dist) {
                nodes[v]->dist = nodes[u]->dist + w;
                q.decreaseKey(v, nodes[v]->dist);
                nodes[v]->setPred(u,e);
            }
        }
    }
}
void Graph::bfs(int v) {
// initialize all nodes as unvisited
    for ( int v=1; v<size; v++) nodes[v]->visited = false ;
    std::queue<int > q; // queue of unvisited nodes
    q.push(v);
    nodes[v]->visited = true ;
    nodes[v]->setPred(v,new Line(Line::START)) ;//
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front ();
        q.pop (); // remove first element of q
        for (auto e : nodes[u]->getAdj()) {
            if(e->null)continue;
            int w = e->getDest()->getNum();
            if (! nodes[w]->visited) { // new node!
                q.push(w);
                nodes[w]->visited = true ;
                nodes[w]->setPred(u,e);//
            }
        }
    }
}

std::list<int> Graph::bfs_path(int a, int b) {
    bfs(a);
    list<int> path;
    if (nodes[b]->visited == false) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v]->getPred();
        path.push_front(v);
    }
    return path;
}

void Graph::addNode(Stop *stop1) {
    nodes.push_back(stop1);
    size = size +1;
}

std::list<int> Graph::dijkstra_cheap_path(int a, int b) {
    dijkstra_Cheap(a);
    list<int> path;
    if (nodes[b]->dist == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v]->getPred();
        path.push_front(v);
    }
    return path;
}

void Graph::dijkstra_Cheap(int s) {
    MinHeap<int, int> q(size, -1);
    map<string,int> values;
    for (int v=1; v<size; v++) {
        nodes[v]->dist = INF;
        q.insert(v, INF);
        nodes[v]->visited = false;
    }
    nodes[s]->dist = 0;
    q.decreaseKey(s, 0);
    nodes[s]->setPred(s,new Line(Line::START)) ;
    values.insert(pair<string,int>(nodes[s]->getZone(),0));
    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u]->visited = true;
        for (auto e : nodes[u]->getAdj()) {
            if(e->null)continue;
            int v = e->getDest()->getNum();
            int w;
            if(values.find(nodes[v]->getZone()) != values.end()){
                w = min(values.find(nodes[v]->getZone())->second,values.find(nodes[u]->getZone())->second+1);
                values.insert(pair<string,int>(nodes[v]->getZone(),w));
            }
            else{
                values.insert(pair<string,int>(nodes[v]->getZone(),values.find(nodes[u]->getZone())->second+1));
                w = values.find(nodes[v]->getZone())->second;
            }
            if (!nodes[v]->visited && nodes[u]->dist + w < nodes[v]->dist) {
                nodes[v]->dist = nodes[u]->dist + w;
                q.decreaseKey(v, nodes[v]->dist);
                nodes[v]->setPred(u,e);
            }
        }
    }
}

std::list<int> Graph::dijkstra_bus_path(int a, int b) {
    dijkstra_bus(a);
    list<int> path;
    if (nodes[b]->dist == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v]->getPred();
        path.push_front(v);
    }
    return path;
}

void Graph::dijkstra_bus(int s) {
    MinHeap<int, int> q(size, -1);
    map<string,int> values;
    for (int v=1; v<size; v++) {
        nodes[v]->dist = INF;
        q.insert(v, INF);
        nodes[v]->visited = false;
    }
    nodes[s]->dist = 0;
    q.decreaseKey(s, 0);
    nodes[s]->setPred(s,new Line(Line::START)) ;
    values.insert(pair<string,int>(nodes[s]->getZone(),0));
    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u]->visited = true;
        for (auto e : nodes[u]->getAdj()) {
            if(e->null)continue;
            int v = e->getDest()->getNum();
            int w;
            if(values.find(nodes[v]->getZone()) != values.end()){
                w = min(values.find(nodes[v]->getZone())->second,values.find(nodes[u]->getZone())->second+1);
                values.insert(pair<string,int>(nodes[v]->getZone(),w));
            }
            else{
                values.insert(pair<string,int>(nodes[v]->getZone(),values.find(nodes[u]->getZone())->second+1));
                w = values.find(nodes[v]->getZone())->second;
            }
            if (!nodes[v]->visited && nodes[u]->dist + w < nodes[v]->dist) {
                nodes[v]->dist = nodes[u]->dist + w;
                q.decreaseKey(v, nodes[v]->dist);
                nodes[v]->setPred(u,e);
            }
        }
    }
}


