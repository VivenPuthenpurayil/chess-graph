#include "graph.h"



Graph::Graph(int num_verticies) : num_verticies_(num_verticies), num_edges_(0) {
    adjacency_matrix_ = std::vector<std::vector<int>>(num_verticies, std::vector<int>(num_verticies, 0));
}

Graph Graph::g_union(Graph & g1, Graph & g2) {

    Graph out(g1.num_verticies());
    if (g1.num_verticies_ != g2.num_verticies_) {
        // this shouldn't happen idk how to handle
        return out;
    }

    for (int i = 0; i < g1.num_verticies(); i++) {
        for (int j = 0; j < g1.num_verticies(); j++) {
            if (g1.adjacency_matrix_[i][j] > 0 || g2.adjacency_matrix_[i][j] > 0) {
                out.num_edges_++;
            }
            out.adjacency_matrix_[i][j] = std::max(g1.adjacency_matrix_[i][j], g2.adjacency_matrix_[i][j]);
        }
    }

    return out;

}

void Graph::insertEdge(int v1, int v2) {
    if (!(std::abs(adjacency_matrix_[v1][v2]) >= 1)) {
        num_edges_++;
    }
    adjacency_matrix_[v1][v2] = 1; // from v1 to v2
}

void Graph::insertEdge(int v1, int v2, int weight) {
    if (!(std::abs(adjacency_matrix_[v1][v2]) >= 1)) {
        num_edges_++;
    }
    adjacency_matrix_[v1][v2] = weight; // from v1 to v2
}

void Graph::removeEdge(int v1, int v2) {
    if (std::abs(adjacency_matrix_[v1][v2]) >= 1) {
        num_edges_--;
    }
    adjacency_matrix_[v1][v2] = 0; // from v1 to v2
}

bool Graph::edgeExists(int v1, int v2) const {
    return std::abs(adjacency_matrix_[v1][v2]) >= 1;
}

int Graph::weight(int v1, int v2) const {
    return adjacency_matrix_[v1][v2];
}

std::list<int> Graph::out_neighbors(int v) const {

    std::list<int> neighbors_;

    for (int j = 0; j < num_verticies_; j++) {
        if (std::abs(adjacency_matrix_[v][j]) >= 1) {   // neighbors that vertex v can travel to
            neighbors_.push_back(j);
        }
    }
    return neighbors_;
}

std::list<int> Graph::in_neighbors(int v) const {

    std::list<int> neighbors_;

    for (int j = 0; j < num_verticies_; j++) {
        if (std::abs(adjacency_matrix_[j][v]) >= 1) {   // neighbors that can travel to vertex v
            neighbors_.push_back(j);
        }
    }
    return neighbors_;
}

std::list<int> Graph::neighbors(int v) const {

    std::list<int> neighbors_;

    for (int j = 0; j < num_verticies_; j++) {
        if (v != j && (std::abs(adjacency_matrix_[j][v]) >= 1 || std::abs(adjacency_matrix_[v][j]) >= 1))  {
            neighbors_.push_back(j);
        }
    }

    return neighbors_;
}

int Graph::in_degree(int v) const {
    int degree_ = 0;

    for (int j = 0; j < num_verticies_; j++) {
        if (std::abs(adjacency_matrix_[j][v]) >= 1) {
            degree_++;
        }
    }
    return degree_;

}

int Graph::out_degree(int v) const {
    int degree_ = 0;

    for (int j = 0; j < num_verticies_; j++) {
        if (std::abs(adjacency_matrix_[v][j]) >= 1) {
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