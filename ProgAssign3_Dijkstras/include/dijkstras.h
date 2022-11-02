#pragma once
#include "./hash.h"
#include "./heap.h"
#include "./graph.h"

int constructGraph(graph& g, std::string filename);

// returns 0 on success
// performs dijkstra's algorithm on the graph
int dijkstra(graph& graph, std::string start);
