#include <string>
#include "../include/graph.h"

bool graph::containsVertex(const std::string &id)
{
    return vertex_table.contains(id);
}

graph::vertex_node* graph::getVertexPointer(const std::string &id)
{
    return (vertex_node*)vertex_table.getPointer(id);
}

void graph::addEdge(const std::string &src, const std::string &dest, int weight)
{
   vertex_node* vDest = getVertexPointer(dest);
   vertex_node* vSrc = getVertexPointer(src);

   if(vSrc == nullptr)
   {
        // create a new vertex
        vertex_node v(src);

        // add the vertex to the vertices vector
        vertices.push_back(v);

        // save the location of the vertex
        vertex_node* vptr = &vertices.back();

        // add the vertex location to the hash table
        vertex_table.insert(src, vptr);

        // set vSrc to the new vertex
        vSrc = vptr;
   }

   if (vDest == nullptr)
    {
        // create a new vertex
        vertex_node v(dest);

        // add the vertex to the vertices vector
        vertices.push_back(v);

        // save the location of the vertex
        vertex_node* vptr = &vertices.back();

        // add the vertex location to the hash table
        vertex_table.insert(dest, vptr);

        // set vDest to the new vertex
        vDest = vptr;
    }

   // create a new edge
   vertex_node::edge_node e(vDest, weight);

   // add the edge to the adjacency list of the source vertex
    vSrc->adj.push_back(e);
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