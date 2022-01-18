// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}


// ----------------------------------------------------------
// Exercicio 3: Algoritmo de Prim
// ----------------------------------------------------------
// TODO
int Graph::prim(int r) {
    for(auto &elemento : nodes){
        elemento.distance = 999999999;
        elemento.parent = -1;
    }
    nodes[r].distance = 0;
    MinHeap<int,int> heap(nodes.size(),-1);
    for(auto &sus : nodes[r].adj){
        heap.insert(sus.dest,sus.weight);
    }
    while (heap.getSize() >1){
        int min = heap.removeMin();
        for(auto &sus :nodes[min].adj){
            if(heap.hasKey(sus.dest) && (sus.weight < nodes[sus.dest].distance)){
                nodes[sus.dest].parent = min;
            }
        }
    }
    return heap.getSize();
}


// ----------------------------------------------------------
// Exercicio 5: Algoritmo de Kruskal
// ----------------------------------------------------------
// TODO
int Graph::kruskal() {
    return 0;
}
