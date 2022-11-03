#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "../include/graph.h"
#include "../include/main.h"

int main()
{
    std::string inputFile;
    std::string startVertex;

    std::cout <<"Enter name of graph file: ";
    std::cin >> inputFile;

    std::cout <<"Enter name of start vertex: ";
    std::cin >> startVertex;

    graph g;
    constructGraph(g, inputFile);

    // start the clock
    auto start = std::chrono::high_resolution_clock::now();

    // run the algorithm
    graph::dijkstra dijk(g, startVertex);

    // stop the clock
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << duration.count() / 1000000.0 << std::endl;

    std::string outputFile;

    std::cout << "Enter name of output file: ";
    std::cin >> outputFile;

    exportResults(dijk, outputFile);
}

void constructGraph(graph &g, std::string inputFile)
{
    // open the file
    std::ifstream file(inputFile);

    // get a line
    std::string line;

    // while there are lines to read
    while (std::getline(file, line))
    {

        // get the words from the line
        std::istringstream iss(line);

        std::string src;
        std::string dest;
        int weight;

        // extract the good stuff
        iss >> src;
        iss >> dest;
        iss >> weight;

        // add the edge to the graph
        g.addEdge(src, dest, weight);
    }

    // close the file
    file.close();
}

void exportResults(graph::dijkstra dijk, std::string outputFile)
{
    // open the file
    std::ofstream file(outputFile);

    // for all the vertices in the graph
    std::vector<std::string> ids = dijk.getVertexIds();
    for (std::string vertex : ids)
    {
        file << vertex << ": ";
        file << dijk.getDistance(vertex) << " ";

        file << "[";
        // get the shortest path
        std::vector<std::string> path = dijk.getShortestPath(vertex);

        // print the shortest path
        for (std::string vertex : path)
        {
            file << vertex;

            if (vertex != path.back())
            {
                file << ", ";
            }
        }
        file << "]" << std::endl;
    }

    // close the file
    file.close();
}
