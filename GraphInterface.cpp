// Alex Smith
// Implementation file for the GraphInterface class

#include "GraphInterface.h"
#include <iostream>

/*------Constructors------*/
GraphInterface::GraphInterface() {}

GraphInterface::GraphInterface(const GraphInterface& orig) {
    copyInterface(orig);
}

/*-------Destructor-------*/
GraphInterface::~GraphInterface() {}

/*-------Operators-------*/
GraphInterface& GraphInterface::operator=(const GraphInterface& orig) {
    if (this != &orig) {
        copyInterface(orig);
    }
    return *this;
}

/*--------Methods--------*/
void GraphInterface::run() {
    string choice;
    bool isEmpty;
    while (true) {
        isEmpty = graph.isEmpty();
        cout << "R- Read Graph" << endl;
        if (!isEmpty) {
            cout << "T- Topological Sort" << endl;
            cout << "S- Shortest Path" << endl;
            cout << "M- Minimum Spanning Tree" << endl;
        }
        cout << "Q- Quit" << endl;
        cout << "Choice: ";
        cin >> choice;
        cout << endl;
        if (choice == "R" || choice == "r") optionRead();
        else if (choice == "Q" || choice == "q") break;
        else if (!isEmpty) {
            if (choice == "T" || choice == "t") optionTop();
            else if (choice == "S" || choice == "s") optionShort();
            else if (choice == "M" || choice == "m") optionMin();
            else cout << choice << " is not an option\n" << endl;;
        }
        else cout << choice << " is not an option\n" << endl;;
    }
}

void GraphInterface::optionRead() {
    string filePath;
    try {
        cout << "Please enter the name of the file to read from (example.txt): ";
        cin >> filePath;
        cout << endl;
        graph.readGraph(filePath);
    } catch(const exception& e) {
        cout << "This file is not format correctly\n" << endl;
        graph.clear();
    }
}

void GraphInterface::optionTop() {
    graph.getTopSort();
}

void GraphInterface::optionShort() {
    string startVertex;
    bool invalid;
    do {
        invalid = false;
        graph.printVertices(cout);
        cout << "What vertex would you like to start at: ";
        cin >> startVertex;
        if (!graph.hasVertex(startVertex)) {
            cout << "\nA vertex with that name does not exist" << endl;
            invalid = true;
        }
    } while (invalid);
    graph.getShortestPaths(startVertex);
}

void GraphInterface::optionMin() {
    graph.getMinSpanTree();
}

void GraphInterface::copyInterface(const GraphInterface& orig) {
    graph = orig.graph;
}