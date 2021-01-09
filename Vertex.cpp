// Alex Smith
// Implementation file for the Vertex class

#include "Vertex.h"

Vertex::Vertex() {
    name = "";
    indegree = 0;
}

Vertex::Vertex(string n) {
    name = n;
    indegree = 0;
}

Vertex::Vertex(const Vertex& orig) {
    copyVertex(orig);
}

/*-------Destructor-------*/
Vertex::~Vertex() {}

/*-------Operators-------*/
Vertex& Vertex::operator=(const Vertex& orig) {
    if (this != &orig) {
        copyVertex(orig);
    }
    return *this;
}

/*--------Methods--------*/
bool Vertex::addEdge(int toIndex, int weight) {
    bool added = false;
    if (!hasEdge(toIndex)) {
        adjacencyList.push_back(Edge(toIndex, weight));
        added = true;
    }
    return added;
}

bool Vertex::hasEdge(int toIndex) {
    bool hasEdge = false;
    for (Edge& edge : adjacencyList) {
        if (toIndex == edge.toIndex) {
            hasEdge = true;
            break;
        }
    }
    return hasEdge;
}

void Vertex::incrementIndegree(){
    indegree++;
}

const string& Vertex::getName() {
    return name;
}

int Vertex::getIndegree() {
    return indegree;
}

const list<Edge>& Vertex::getAdjacencyList() {
    return adjacencyList;
}

void Vertex::copyVertex(const Vertex& orig) {
    name = orig.name;
    indegree = orig.indegree;
    adjacencyList = orig.adjacencyList;
}