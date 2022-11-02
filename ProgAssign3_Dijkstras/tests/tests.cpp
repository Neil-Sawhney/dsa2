#include "../include/graph.h"
#include <iostream>

bool graph::test1(){
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
        return false;

    return true;
}

void performAllTests()
{
    graph g;
    
    if (g.test1())
        std::cout << "Test 1 passed" << std::endl;
    else
        std::cout << "Test 1 failed" << std::endl;
}
