#pragma once
#include <string>
#include "./graph.h"

// constructs a graph from a file
void constructGraph(graph &g, std::string inputFile);

// exports the results of the algorithm to a file following sables format
void exportResults(graph::dijkstra dijk, std::string outputFile);
