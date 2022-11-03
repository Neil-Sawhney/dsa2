#include <string>
#include <list>
#include "../include/heap.h"
#include "../include/graph.h"

graph::dijkstra::destination_vertex* graph::dijkstra::getDestinationPointer(const std::string &id)
{
    return (destination_vertex*)destinationTable.getPointer(id);
}

graph::dijkstra::dijkstra(graph &graph, std::string srcId) : destinationTable(2*graph.vertices.size())
{
    // create a heap to get the minimum distance to the next unknown vertex
    heap unknownVertices(graph.vertices.size());

    // create a destination node for each vertex in the graph
    for (vertex_node &v : graph.vertices)
    {
        // add it to the list of destinations
        destinations.push_back(destination_vertex(&v));

        // save the loaction of the destination in the list
        destination_vertex* loc = &destinations.back();
        
        // add it to the hash table
        destinationTable.insert(v.id, loc);

        // add it to the heap
        unknownVertices.insert(v.id, INT_MAX, loc);
    }  

    // set the distance to the source vertex to 0
    getDestinationPointer(srcId)->distance = 0;

    // update the heap
    unknownVertices.setKey(srcId, 0);

    std::string id;
    int key;
    destination_vertex* v; 

    // while there are still unknown vertices
    while (unknownVertices.deleteMin(&id, &key, &v) != heap::returnValues::HEAP_EMPTY)
    {
        // set known to true for the unknown vertex with the minimum distance
        v->known = true;

        // for each edge in the adjacency list of the vertex
        for (vertex_node::edge_node e : v->vertex->adj)
        {
            // define w as the destination vertex of the edge
            destination_vertex* w = getDestinationPointer(e.dest->id);

            // if the distance to v + the weight of e is less than the distance to w
            if (v->distance + e.weight < w->distance && !w->known)
            {
                w->distance = v->distance + e.weight;
                w->prevVertex = v->vertex;

                // update the heap
                unknownVertices.setKey(e.dest->id, w->distance);
            }
        }

    }

}

graph::dijkstra::destination_vertex::destination_vertex(vertex_node* vertex)
{
    this->vertex = vertex;
}

int graph::dijkstra::getDistance(const std::string &destId)
{
    return getDestinationPointer(destId)->distance;
}

std::vector<std::string> graph::dijkstra::getShortestPath(const std::string &destId)
{
    std::vector<std::string> path;
    destination_vertex* v = getDestinationPointer(destId);

    // while the previous vertex is not null
    while (v->prevVertex != nullptr)
    {
        // add the id of the vertex to the path
        path.push_back(v->vertex->id);

        // set v to the previous vertex
        v = getDestinationPointer(v->prevVertex->id);
    }

    // add the source vertex to the path
    path.push_back(v->vertex->id);

    // reverse the path
    std::reverse(path.begin(), path.end());

    return path;
}