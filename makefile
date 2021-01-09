CC=g++
CFLAGS=-std=c++11

all:Vertex DirectedGraph GraphInterface runProgram
	$(CC) $(CFLAGS) Vertex.o DirectedGraph.o GraphInterface.o runProgram.o -o out
Vertex:Vertex.cpp
	$(CC) $(CFLAGS) -c Vertex.cpp
DirectedGraph:DirectedGraph.cpp
	$(CC) $(CFLAGS) -c DirectedGraph.cpp
GraphInterface:GraphInterface.cpp
	$(CC) $(CFLAGS) -c GraphInterface.cpp
runProgram:runProgram.cpp
	$(CC) $(CFLAGS) -c runProgram.cpp
clean:
	rm *.o out