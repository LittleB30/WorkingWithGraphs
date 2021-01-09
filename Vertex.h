// Alex Smith
// Header file for a Vertex class that 

#ifndef VERTEX_H
#define VERTEX_H

#include <list>
#include <string>

using namespace std;

struct Edge {
    int toIndex;
    int weight;

    Edge() {
        toIndex = -1;
        weight = 0;
    }

    Edge(int to, int w) {
        toIndex = to;
        weight = w;
    }
};

class Vertex {
private:
    string name;
    int indegree;
    list<Edge> adjacencyList;

public:
    /*------Constructors------*/
    Vertex();
    Vertex(string n);
    Vertex(const Vertex& orig);

    /*-------Destructor-------*/
    virtual ~Vertex();

    /*-------Operators-------*/
    Vertex& operator=(const Vertex& orig);
    
    /*--------Methods--------*/
    bool addEdge(int toIndex, int weight);
    bool hasEdge(int toIndex);
    void incrementIndegree();
    const string& getName();
    int getIndegree();
    const list<Edge>& getAdjacencyList();

private:
    void copyVertex(const Vertex& orig);
};

#endif
