#pragma once
#include <list>
#include <vector>
#include <algorithm>

class Graph {
/**
 * Need to provide an outside label-to-index mapping
*/
public:

    Graph(int size);

    void insertEdge(int v1, int v2);
    void removeEdge(int v1, int v2);
    
    std::list<int> out_neighbors(int v) const;
    std::list<int> in_neighbors(int v) const;

    std::list<int> neighbors(int v) const;

    bool edgeExists(int v1, int v2) const;

    int degree(int v) const; // This is the sum of in + out, however this means we are double counting bidirectional edges.
    int in_degree(int v) const;
    int out_degree(int v) const;

    int num_verticies() const;
    int num_edges() const;


private:
    std::vector<std::vector<int>> adjacency_matrix_;
    const int num_verticies_;
    int num_edges_;


};