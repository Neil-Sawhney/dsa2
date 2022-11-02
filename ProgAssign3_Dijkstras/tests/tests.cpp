#include "../include/graph.h"
#include <iostream>

bool graph::tests(){

    // test 1
    try {
        // make a graph and add some edges to it
        addEdge("A", "B", 1);
        addEdge("A", "C", 2);
        addEdge("B", "C", 3);
        addEdge("B", "D", 4);
        addEdge("C", "D", 5);
        addEdge("C", "E", 6);
        addEdge("D", "E", 7);
        addEdge("D", "F", 8);
        addEdge("E", "F", 9);

        // check if the graph contains the vertices we added
        if(!containsVertex("A") || !containsVertex("B") || !containsVertex("C") || !containsVertex("D") || !containsVertex("E") || !containsVertex("F"))
            throw "containsVertex() returned false for a vertex that was added to the graph";
        
    }
    catch (const char* msg) {
        std::cerr << msg << std::endl;
        return false;
    };

    // test 2
    try {
        // make sure the edges are where they are supposed to be 
        if (getVertexPointer("A")->adj.front().dest->id != "B")
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("A")->adj.front().weight != 1)
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("A")->adj.back().dest->id != "C")
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("A")->adj.back().weight != 2)
            throw "edge not added correctly at line" + std::to_string(__LINE__);

        if (getVertexPointer("B")->adj.front().dest->id != "C")
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("B")->adj.front().weight != 3)
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("B")->adj.back().dest->id != "D")
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("B")->adj.back().weight != 4)
            throw "edge not added correctly at line" + std::to_string(__LINE__);

        if (getVertexPointer("C")->adj.front().dest->id != "D")
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("C")->adj.front().weight != 5)
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("C")->adj.back().dest->id != "E")
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("C")->adj.back().weight != 6)
            throw "edge not added correctly at line" + std::to_string(__LINE__);

        if (getVertexPointer("D")->adj.front().dest->id != "E")
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("D")->adj.front().weight != 7)
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("D")->adj.back().dest->id != "F")
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("D")->adj.back().weight != 8)
            throw "edge not added correctly at line" + std::to_string(__LINE__);

        if (getVertexPointer("E")->adj.front().dest->id != "F")
            throw "edge not added correctly at line" + std::to_string(__LINE__);
        if (getVertexPointer("E")->adj.front().weight != 9)
            throw "edge not added correctly at line" + std::to_string(__LINE__);
    }
    catch (std::string msg) {
        std::cerr << msg << std::endl;
        return false;
    };

    return true;
}

void performTests(){
    graph g;
    if ( g.tests() )
        std::cout << "All tests passed!" << std::endl;
    else
        std::cout << "Some tests failed" << std::endl;
}