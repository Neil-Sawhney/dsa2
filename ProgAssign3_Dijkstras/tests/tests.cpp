#include "../include/graph.h"
#include <iostream>

bool test1(){
    // make a graph and add some edges to it
    graph g;

    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 2);
    g.addEdge("B", "C", 3);
    g.addEdge("B", "D", 4);
    g.addEdge("C", "D", 5);
    g.addEdge("C", "E", 6);
    g.addEdge("D", "E", 7);
    g.addEdge("D", "F", 8);
    g.addEdge("E", "F", 9);

    // check if the graph contains the vertices we added
    if(!g.containsVertex("A") || !g.containsVertex("B") || !g.containsVertex("C") || !g.containsVertex("D") || !g.containsVertex("E") || !g.containsVertex("F"))
        return false;

    return true;
}

void performAllTests()
{
    if (test1())
        std::cout << "Test 1 passed" << std::endl;
    else
        std::cout << "Test 1 failed" << std::endl;
}
