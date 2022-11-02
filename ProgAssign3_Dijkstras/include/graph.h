#pragma once
#include "../include/hash.h"
#include <string>
#include <list>
#include <vector>

class graph
{
    private:
        // Each vertex node in the graph contains:
        // id - a string that identifies the vertex.
        // adj - a list containing all adjacent edges
        class vertex_node
        {
            public:
            // each edge node in the graph contains:
            // dest - a pointer to the destination vertex
            // weight - the weight of the edge
            class edge_node
            {
                public:
                vertex_node* dest; // The destination vertex
                int weight; // The weight of the edge
                
                edge_node(vertex_node* &dest, int weight); // The constructor
            };

            std::string id{""}; // A string that identifies the vertex

            // A list of all adjacent edges
            // each node in the adjacency list represents an edge
            std::list<edge_node> adj;

            vertex_node(const std::string &id); // The constructor
        };

        // a vector of all the vertices in the graph
        std::vector<vertex_node> vertices;
        hashTable vertex_table; // A hash table that maps vertex ids to vertex nodes

    public:

    //TODO: do we need a constructor to initialize the hash table / heap?

    // adds an edge to the graph
    void addEdge(const std::string &src, const std::string &dest, int weight);

    // returns true if the vertex is in the graph
    bool containsVertex(const std::string &id);

    // returns a pointer to the vertex node with the specified id
  // If the vertex DNE return nullptr
    vertex_node* getVertexPointer(const std::string &id);

    // TODO: these are tests, comment them out later
    bool test1();
};