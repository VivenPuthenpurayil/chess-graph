#pragma once
#include <list>
#include <vector>
#include <algorithm>

class Graph {
/**
 * Need to provide an outside label-to-index mapping
*/
public:

    
    /**
      * Creates a graph object of @param size
      */
    Graph(int size);

    static Graph g_union(Graph & g1, Graph & g2); // Union of two graphs

    void insertEdge(int v1, int v2);            // Default implementation where weight is 1
    void insertEdge(int v1, int v2, int weight);
    void removeEdge(int v1, int v2);
    
    std::list<int> out_neighbors(int v) const;  // list of neighbors that you can travel to from this vertex
    std::list<int> in_neighbors(int v) const;   // list neighbors that can travel to this vertex

    std::list<int> neighbors(int v) const;      // List of both in and out neighbors

    bool edgeExists(int v1, int v2) const;
    bool undirectedEdgeExists(int v1, int v2) const;  // Checks if there is an edge going from v1 to v2 or v2 to v1
    int weight(int v1, int v2) const;           // weight of the edge from v1 to v2

    int degree(int v) const;                    // This is the sum of in + out, however this means we are double counting bidirectional edges.
    int out_degree(int v) const;                // number of neighbors that you can travel to from this vertex
    int in_degree(int v) const;                 // number of neighbors that can travel to this vertex

    int num_verticies() const;                  // Total number of verticies in the graph
    int num_edges() const;                      // Total number of edges in the graph


private:
    std::vector<std::vector<int>> adjacency_matrix_;
    const int num_verticies_;
    int num_edges_;

};