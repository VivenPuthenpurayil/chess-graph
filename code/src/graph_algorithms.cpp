#include "graph_algorithms.h"

int average_degree(const Graph& g) {
    int num = 0;
    for (int i = 0; i < g.num_verticies(); i++) {
        num += g.degree(i);
        num /= 2;
    }
    return num;

}

int max_degree(const Graph& g) {
    int max = 0;
    for (int i = 0; i < g.num_verticies(); i++) {
        if (g.degree(i) > max) {
            max = g.degree(i);
        }
    }
    return max;
}

std::vector<int> tarjans(const Graph& g) {

    int size = g.num_verticies();
    int count = 0;
    int id = 0;

    // For Tarjans
    std::vector<int> lowlink (size, 0); // Store low link values of each node
    std::stack<int> ll_stack; // store if they are on the tarjans stack
    std::vector<bool> on_stack (size, false);
    std::vector<int> ids (size, 0);

    // For our DFS
    std::vector<bool> visited (size, false);

    for (int i = 0; i < size; i++) {
        // Make sure we get every connected component
        if (visited[i] == true) {
            continue;
        }
        tarjans_(i, g, lowlink, ll_stack, on_stack, visited, id, ids);
    }
    return lowlink;
}


void tarjans_(int v, const Graph& g, std::vector<int> & lowlink, std::stack<int> & ll_stack, std::vector<bool> & on_stack, std::vector<bool> &visited, int & id, std::vector<int> & ids) {
    ll_stack.push(v);
    on_stack[v] = true;
    visited[v] = true;
    lowlink[v] = id;
    ids[v] = id++;

    for(int n : g.out_neighbors(v)) {
        if (visited[n] == false) {
            tarjans_(n, g, lowlink, ll_stack, on_stack, visited, id, ids);
        }
        if (on_stack[n] == true) {
            lowlink[v] = std::min(lowlink[v], lowlink[n]);
        }
    }

    if (lowlink[v] == ids[v]) {
        while (!ll_stack.empty()) {
            int i = ll_stack.top();
            ll_stack.pop();
            lowlink[i] = ids[v];
            on_stack[i] = false;
            if (i == v) {
                break;
            }
        }
    }
}