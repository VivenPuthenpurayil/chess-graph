#include "graph.h"



Graph::Graph(int num_verticies) : num_verticies_(num_verticies), num_edges_(0) {
    adjacency_matrix_ = std::vector<std::vector<int>>(num_verticies, std::vector<int>(num_verticies, 0));
}

void Graph::insertEdge(int v1, int v2) {
    if (!adjacency_matrix_[v1][v2]) {
        num_edges_++;
    }
    adjacency_matrix_[v1][v2] = 1; // from v1 to v2
}

void Graph::removeEdge(int v1, int v2) {
    if (adjacency_matrix_[v1][v2]) {
        num_edges_--;
    }
    adjacency_matrix_[v1][v2] = 0; // from v1 to v2
}

bool Graph::edgeExists(int v1, int v2) const {
    return adjacency_matrix_[v1][v2];
}

std::list<int> Graph::out_neighbors(int v) const {

    std::list<int> neighbors_;

    for (int j = 0; j < num_verticies_; j++) {
        if (adjacency_matrix_[v][j] == 1) {
            neighbors_.push_back(j);
        }
    }
    return neighbors_;
}

std::list<int> Graph::in_neighbors(int v) const {

    std::list<int> neighbors_;

    for (int j = 0; j < num_verticies_; j++) {
        if (adjacency_matrix_[j][v] == 1) {
            neighbors_.push_back(j);
        }
    }
    return neighbors_;
}

std::list<int> Graph::neighbors(int v) const {

    std::list<int> neighbors_;

    for (int j = 0; j < num_verticies_; j++) {
        if (v == j) {
            continue;
        }
        if (adjacency_matrix_[j][v] == 1 || adjacency_matrix_[v][j] == 1)  {
            neighbors_.push_back(j);
        }
    }

    return neighbors_;
}

int Graph::out_degree(int v) const {
    int degree_ = 0;

    for (int j = 0; j < num_verticies_; j++) {
        if (adjacency_matrix_[v][j] == 1) {
            degree_++;
        }
    }
    return degree_;

}

int Graph::in_degree(int v) const {
    int degree_ = 0;

    for (int j = 0; j < num_verticies_; j++) {
        if (adjacency_matrix_[j][v] == 1) {
            degree_++;
        }
    }
    return degree_;

}

int Graph::degree(int v) const {
    return in_degree(v) + out_degree(v);

}

int Graph::num_verticies() const {
    return num_verticies_;
}

int Graph::num_edges() const {
    return num_edges_;
}