// Alex Smith
// Implementation file for the DirectedGraph class

#include "DirectedGraph.h"
#include <fstream>
#include <sstream>
#include <list>
#include <stack>
#include <iostream>

/*------Constructors------*/
DirectedGraph::DirectedGraph() {}

DirectedGraph::DirectedGraph(const DirectedGraph& orig) {
    copyGraph(orig);
}

/*-------Destructor-------*/
DirectedGraph::~DirectedGraph() {}

/*-------Operators-------*/
DirectedGraph& DirectedGraph::operator=(const DirectedGraph& orig) {
    if (this != &orig) {
        copyGraph(orig);
    }
    return *this;
}

/*--------Methods--------*/
void DirectedGraph::readGraph(const string& fileName) {
    clear();
    ifstream inFile(fileName);
    readVertices(inFile);
    readEdges(inFile);
    inFile.close();
}

void getIndegrees(vector<Vertex>& vertices, vector<int>& indegrees) {
    int index = 0;
    for (Vertex& vertex : vertices) {
        indegrees.push_back(vertices[index++].getIndegree());
    }
}

void enqueueIndegreesOfZero(vector<int>& indegrees, queue<int>& queue) {
    int index = 0;
    for (int& indegree : indegrees) {
        if (indegree == 0) {
            queue.push(index);
            indegree--;
        }
        ++index;
    }
}

void decrementAdjacentVertices(vector<Vertex>& vertices, vector<int>& indegrees, const int curVertex) {
    for (const Edge& edge : vertices[curVertex].getAdjacencyList()) {
        indegrees[edge.toIndex]--;
    }
}

void printTopSort(const list<string>& topOrder, const bool hasCycle) {
    if (hasCycle) {
        cout << "This graph has a cycle so a topological sort is not possible" << endl;
    } else {
        for (const string& str : topOrder) {
            cout << str << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void DirectedGraph::getTopSort() {
    vector<int> indegrees;
    queue<int> sorting;
    list<string> topOrder;

    bool hasCycle = false;
    getIndegrees(vertices, indegrees);
    for (int index = 0; index < vertices.size() && !hasCycle; index++) {
        enqueueIndegreesOfZero(indegrees, sorting);
        if (sorting.empty()) {
            hasCycle = true;
        } else {
            topOrder.push_back(vertices[sorting.front()].getName());
            decrementAdjacentVertices(vertices, indegrees, sorting.front());
            sorting.pop();
        }
    }
    printTopSort(topOrder, hasCycle);
}

pair<Path,bool> hasPath(vector<Path>& shortestPaths, int toVertex) {
    Path* temp;
    bool hasPath = false;
    for (Path& path : shortestPaths) {
        if (path.toVertex == toVertex) {
            temp = &path;
            hasPath = true;
            break;
        }
    }
    return make_pair(*temp, hasPath);
}

void DirectedGraph::getShortestPaths(const string& startVertex) {
    vector<Path> shortestPaths;
    priority_queue<Path> paths;
    int start = findVertex(startVertex);
    paths.push(Path(start, start, 0));
    while (!paths.empty()) {
        const Path& curPath = paths.top();
        if (!hasPath(shortestPaths, curPath.toVertex).second) {
            findPaths(curPath.toVertex, shortestPaths, paths);
            shortestPaths.push_back(curPath);
        }
        paths.pop();
    }
    printPaths(shortestPaths);
}

void DirectedGraph::getMinSpanTree() {
    //you've bested me this time min span tree
}

bool DirectedGraph::hasVertex(const string& vertexName) {
    bool hasVertex = false;
    if (findVertex(vertexName) != -1) {
        hasVertex = true;
    }
    return hasVertex;
}

bool DirectedGraph::isEmpty() {
    return vertices.empty();
}

void DirectedGraph::clear() {
    vertices.clear();
}

void DirectedGraph::printVertices(ostream& outStream) {
    outStream << "Vertices: ";
    for (Vertex& vertex : vertices) {
        outStream << vertex.getName() << " ";
    }
    outStream << endl;
}

void DirectedGraph::readVertices(ifstream& inFile) {
    string temp;
    inFile >> temp;
    for (int i = 0, numVertices = stoi(temp); i < numVertices; i++) {
        inFile >> temp;
        addVertex(temp);
    }
}

void DirectedGraph::readEdges(ifstream& inFile) {
    string temp;
    string from;
    string to;
    string weight;
    inFile >> temp;
    for (int i = 0, numEdges = stoi(temp); i < numEdges; i++) {
        inFile >> from;
        inFile >> to;
        inFile >> weight;
        addEdge(from, to, stoi(weight));
    }
}

int DirectedGraph::findVertex(const string& vertexName) {
    int index = 0;
    for (Vertex& vertex : vertices) {
        if (vertexName == vertex.getName()) {
            break;
        }
        index++;
    }
    if (index == vertices.size()) {
        index = -1;
    }
    return index;
}

bool DirectedGraph::addVertex(const string& vertexName) {
    bool added = false;
    if (!hasVertex(vertexName)) {
        vertices.push_back(Vertex(vertexName));
        added = true;
    }
    return added;
}

void DirectedGraph::printPaths(vector<Path> shortestPaths) {
    stack<string> strPath;
    int totalCost;
    Path temp;
    for (Path& path : shortestPaths) {
        temp = path;
        totalCost = path.cost;
        strPath.push(vertices[path.toVertex].getName());
        while (temp.fromVertex != temp.toVertex) {
            temp = hasPath(shortestPaths, temp.fromVertex).first;
            strPath.push(vertices[temp.toVertex].getName());
            totalCost += temp.cost;
        }
        while (!strPath.empty()) {
            cout << strPath.top() << " ";
            strPath.pop();
        }
        cout << "(" << totalCost << ")" << endl;
    }
}

bool DirectedGraph::addEdge(const string& fromVertex, const string& toVertex, const int weight) {
    bool added = false;
    tuple<int,int,bool> temp = hasEdge(fromVertex, toVertex);
    if (!get<2>(temp)) {
        vertices[get<0>(temp)].addEdge(get<1>(temp), weight);
        vertices[get<1>(temp)].incrementIndegree();
        added = true;
    }
    return added;
}

tuple<int,int,bool> DirectedGraph::hasEdge(const string& fromVertex, const string& toVertex) {
    int fromIndex = findVertex(fromVertex);
    int toIndex = findVertex(toVertex);
    bool hasEdge = vertices[fromIndex].hasEdge(toIndex);
    return make_tuple(fromIndex, toIndex, hasEdge);
}

void DirectedGraph::findPaths(const int fromVertex, vector<Path>& shortestPaths, priority_queue<Path>& paths) { 
    for (const Edge& edge : vertices[fromVertex].getAdjacencyList()) {
        if (!hasPath(shortestPaths, edge.toIndex).second) {
            paths.push(Path(fromVertex, edge.toIndex, edge.weight));
        }
    }
}

void DirectedGraph::copyGraph(const DirectedGraph& orig) {
    vertices = orig.vertices;
}