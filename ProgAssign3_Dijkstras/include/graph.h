#pragma once
#include "../include/hash.h"
#include <string>
#include <list>
#include <vector>
#include <bits/stdc++.h>

class graph
{
    private:
        // Each vertex node in the graph contains:
        // id - a string that identifies the vertex.
        // adj - a list containing all adjacent edges
        struct vertex_node
        {
            // each edge node in the graph contains:
            // dest - a pointer to the destination vertex
            // weight - the weight of the edge
            struct edge_node
            {
                vertex_node* dest{nullptr}; // The destination vertex
                int weight; // The weight of the edge
                
                edge_node(vertex_node* &dest, int weight); // The constructor
            };

            std::string id{""}; // A string that identifies the vertex

            // A list of all adjacent edges
            // each node in the adjacency list represents an edge
            std::list<edge_node> adj;

            vertex_node(const std::string &id); // The constructor

        };

    hashTable vertexTable; // A hash table that maps vertex ids to vertex nodes
    std::list<vertex_node> vertices; // a list of all the vertices in the graph

    public:

    std::vector<std::string> getVertexIds(); // Returns a vector containing all vertex ids

    // adds an edge to the graph
    void addEdge(const std::string &src, const std::string &dest, int weight);

    // returns true if the vertex is in the graph
    bool containsVertex(const std::string &id);

    // returns a pointer to the vertex node with the specified id
    // If the vertex DNE return nullptr
    vertex_node* getVertexPointer(const std::string &id);

    //TODO: whenever we construct a new dijkstra_data, make sure the source exists in the graph
    // stores all the dijkstra data for a source vertex
    struct dijkstra
    {
        struct destination_vertex
        {
            bool known{false}; // true if the shortest path to this vertex is known
            int distance{INT_MAX}; // the distance from the source to this vertex
            vertex_node* prevVertex{nullptr}; // the previous vertex on the shortest path
            vertex_node* vertex{nullptr}; // the vertex this node represents

            destination_vertex(vertex_node* vertex); // The constructor
        };

        std::list<destination_vertex> destinations; // a list of all the destination vertex nodes
        hashTable destinationTable; // a hash table that maps vertex ids to destination vertex nodes

        // returns the shortest path from the source to the destination as a vector of strings
        std::vector<std::string> getShortestPath(const std::string &destId);

        // returns the distance from the source to the destination
        int getDistance(const std::string &destId);

        //TODO: its stupid that i have to redefine this 
        std::vector<std::string> getVertexIds(); // Returns a vector containing all vertex ids


        destination_vertex* getDestinationPointer(const std::string &id); // returns a pointer to the destination vertex node with the specified id

        dijkstra(graph &graph, std::string srcId); // the constructor, dijkstras algorithm is run here
    };

};