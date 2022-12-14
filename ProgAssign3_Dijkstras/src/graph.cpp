#include <string>
#include <vector>
#include <list>
#include "../include/graph.h"

std::vector<std::string> graph::getVertexIds()
{
    std::vector<std::string> ids;
    for (auto &vertex : vertices)
    {
        ids.push_back(vertex.id);
    }
    return ids;
}

bool graph::containsVertex(const std::string &id)
{
    return vertexTable.contains(id);
}

graph::vertex_node* graph::getVertexPointer(const std::string &id)
{
    return (vertex_node*)vertexTable.getPointer(id);
}

void graph::addEdge(const std::string &src, const std::string &dest, int weight)
{
   vertex_node* vDest_ptr = getVertexPointer(dest);
   vertex_node* vSrc_ptr = getVertexPointer(src);

   if(vSrc_ptr == nullptr)
   {
        // add a new vertex node to the vertices list
        vertices.push_back(vertex_node(src));

        // save the location of the vertex
        vSrc_ptr = &vertices.back();

        // add the vertex to the hash table
        vertexTable.insert(src, vSrc_ptr);
   }

   if (vDest_ptr == nullptr)
    {
        // add a new vertex node to the vertices list
        vertices.push_back(vertex_node(dest));

        // save the location of the vertex
        vDest_ptr = &vertices.back();

        // add the vertex to the hash table
        vertexTable.insert(dest, vDest_ptr);
    }

   // add the edge to the adjacency list of the source vertex
    vSrc_ptr->adj.push_back(vertex_node::edge_node(vDest_ptr, weight));
}

//define vertex_node constructor
graph::vertex_node::vertex_node(const std::string &id)
{
    this->id = id;
}

//define edge_node constructor
graph::vertex_node::edge_node::edge_node(vertex_node* &dest, int weight)
{
    this->dest = dest;
    this->weight = weight;
}