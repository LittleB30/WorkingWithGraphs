// Alex Smith
// Header file for a GraphInterface class that 

#ifndef GRAPHINTERFACE_H
#define GRAPHINTERFACE_H

#include "DirectedGraph.h"

class GraphInterface {
private:
    DirectedGraph graph;

public:
    /*------Constructors------*/
    GraphInterface();
    GraphInterface(const GraphInterface& orig);

    /*-------Destructor-------*/
    virtual ~GraphInterface();

    /*-------Operators-------*/
    GraphInterface& operator=(const GraphInterface& orig);
    
    /*--------Methods--------*/
    void run();

private:
    // Postconditions: a new DirectedGraph has been inserted into graphs
    void optionRead();
    
    // Postconditions: a topological sort of the graph indicated by the user has been output
    void optionTop();

    // Postconditions: all shortest paths of the graph indicated by the user has been output
    void optionShort();

    // Postconditions: a minimum spanning tree of the graph indicated by the user has been output
    void optionMin();

    // Postconditions: this and "orig" have identical instance variables
    void copyInterface(const GraphInterface& orig);
};

#endif