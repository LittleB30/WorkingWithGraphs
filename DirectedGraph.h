// Alex Smith
// Header file for a DirectedGraph class that 

#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include "Vertex.h"
#include <string>
#include <tuple>
#include <queue>

using namespace std;

struct Path {
    int fromVertex;
    int toVertex;
    int cost;

    Path(){
        fromVertex = -1;
        toVertex = -1;
        cost = 0;
    }

    Path(int fV, int tV, int c) {
        fromVertex = fV;
        toVertex = tV;
        cost = c;
    }

    bool operator<(const Path& rhs) const {
        return cost < rhs.cost;
    }
};

class DirectedGraph {
private:
    vector<Vertex> vertices;

public:

    /*------Constructors------*/
    DirectedGraph();
    DirectedGraph(const DirectedGraph& orig);

    /*-------Destructor-------*/
    virtual ~DirectedGraph();

    /*-------Operators-------*/
    DirectedGraph& operator=(const DirectedGraph& orig);
    
    /*--------Methods--------*/
    // Preconditions:  "file" is correctly format and in the current directory
    // Postconditions: "file" has been read into the DirectedGraph
    void readGraph(const string& fileName);
    
    // Postconditions: a topological sort of the DirectedGraph has been output
    // Exceptions:     if a topological sort is not possible then an error message is output
    void getTopSort();

    // Preconditions:  "startVertex" is in the DirectedGraph
    // Postconditions: the shortest path from the vertex to all other vertices is output
    // Exceptions:     if a vertex cannot be reached then that vertex is not output
    void getShortestPaths(const string& startVertex);

    // Preconditions:  the DirectedGraph is connected
    // Postconditions: a minimum spanning tree of the DirectedGraph has been output
    void getMinSpanTree();

    bool hasVertex(const string& vertexName);
    bool isEmpty();
    void clear();
    void printVertices(ostream& outStream);

private:
    void readVertices(ifstream& inFile);
    void readEdges(ifstream& inFile);
    int findVertex(const string& vertexName);
    void printPaths(vector<Path> shortestPaths);

    // Postconditions: a vertex with name "vertexName" is added to the vertices vector
    // Returns:        true if added, false if already present
    bool addVertex(const string& vertexName);

    bool addEdge(const string& fromVertex, const string& toVertex, const int weight);
    tuple<int,int,bool> hasEdge(const string& fromVertex, const string& toVertex);

    // Postconditions: priority_queue "paths" contains Paths from curVertex to its adjacent vertices
    void findPaths(const int fromVertex, vector<Path>& shortestPaths, priority_queue<Path>& paths);

    // Postconditions: this and "orig" have identical instance variables
    void copyGraph(const DirectedGraph& orig);
};

#endif
