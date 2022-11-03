#include "../include/graph.h"
#include <vector>
#include <iostream>

void performTests(){
        graph g;

        g.addEdge("v1", "v2", 2);
        g.addEdge("v1", "v4", 1);
        g.addEdge("v2", "v4", 3);
        g.addEdge("v2", "v5", 10);
        g.addEdge("v3", "v1", 4);
        g.addEdge("v3", "v6", 5);
        g.addEdge("v4", "v3", 2);
        g.addEdge("v4", "v5", 2);
        g.addEdge("v4", "v6", 8);
        g.addEdge("v4", "v7", 4);
        g.addEdge("v5", "v7", 6);
        g.addEdge("v7", "v6", 1);

        // dijkstras from v1
        graph::dijkstra v1(g, "v1");

        if(v1.getDistance("v1") != 0)
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getDistance("v2") != 2)
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getDistance("v3") != 3)
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getDistance("v4") != 1)
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getDistance("v5") != 3)
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getDistance("v6") != 6)
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getDistance("v7") != 5)
            throw std::runtime_error("Line: " + std::to_string(__LINE__));

        if(v1.getShortestPath("v1") != std::vector<std::string>({"v1"}))
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getShortestPath("v2") != std::vector<std::string>({"v1", "v2"}))
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getShortestPath("v3") != std::vector<std::string>({"v1", "v4", "v3"}))
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getShortestPath("v4") != std::vector<std::string>({"v1", "v4"}))
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getShortestPath("v5") != std::vector<std::string>({"v1", "v4", "v5"}))    
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getShortestPath("v6") != std::vector<std::string>({"v1", "v4", "v6"}))
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        if(v1.getShortestPath("v7") != std::vector<std::string>({"v1", "v4", "v7"}))
            throw std::runtime_error("Line: " + std::to_string(__LINE__));
        
        // dijkstras from v5
        //graph::dijkstra v5(g, "v5");
}