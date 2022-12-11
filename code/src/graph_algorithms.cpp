#include "graph_algorithms.h"

float average_degree(const Graph& g) {
    float num = 0;
    for (int i = 0; i < g.num_verticies(); i++) {
        if (g.degree(i) > 0) {
            num += g.degree(i);
            num /= 2;
        }
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

int max_size_scc(std::vector<int> lowlink) {

    std::map<int, int> sizes;
    for (int i : lowlink) {
        sizes[i]++;
    }

    int max_size = std::max_element(sizes.begin(), sizes.end(),  
    [] (const std::pair<int, int> & p1, const std::pair<int, int> & p2) {
        return p1.second < p2.second;}
    )->second;

    return max_size;
}

int num_scc(std::vector<int> lowlink) {
    int s = (int) lowlink.size();

    std::sort(lowlink.begin(), lowlink.end());
    auto last = std::unique(lowlink.begin(), lowlink.end());
    lowlink.resize(std::distance(lowlink.begin(), last));

    return lowlink.size();
}

int num_large_scc(std::vector<int> lowlink, int size) {
    int s = (int) lowlink.size();

    std::sort(lowlink.begin(), lowlink.end());

    int limit = size; // How big the sccs have to be

    int curr = lowlink[0];
    int count = 0;
    int out = 0;

    for (int i : lowlink) {
        if (curr == i) {
            count++;
        }
        else if (curr != i){
            if (count > limit) {
                out++;
            }
            curr = i;
            count = 1;
        }
    }
    if (count > limit) {
        out++;
    }
    return out;
}

std::vector<int> purge_small_ll(std::vector<int> lowlink, int size) {
    // Replace the sccs that are too small with -1;
    int s = (int) lowlink.size();

    int limit = size; // How big the sccs have to be

    int curr = lowlink[0];
    int count = 0;
    std::vector<int> survivors(s, 0);

    for (int i : lowlink) {
        if (i == -1) {
            continue;
        }
        survivors[i]++;
    }
    for (int i = 0; i < s; i++) {
        if (lowlink[i] == -1) {
            continue;
        }
        // Not greater than the limit
        if (survivors[lowlink[i]] <= limit) {
            lowlink[i] = -1;
        }
    }
    return lowlink;
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

std::vector<std::vector<int>> weaklyconnected(const Graph& g){  //might need undirected
    std::vector<std::vector<int>> components;
    unsigned size = g.num_verticies();
    std::vector<bool> visited(size,false);
    for(unsigned i=0;i<size;i++){
        if(!visited[i]){
            std::vector<int> c;
            findConnected(i,visited,c,g);
            for (auto i : c) {
            }
            if (!c.empty()) {
                components.push_back(c);
            }
        }
    }
    return components;
}

void findConnected(int node, std::vector<bool>& visited, std::vector<int>& component, Graph g){
    visited[node] = true;
    component.push_back(node);
    for(auto i:g.neighbors(node)){
        if(!(visited[i])){
            findConnected(i,visited,component,g);
        }
    }

}

std::vector<std::vector<int>> eulerian(Graph g, std::vector<std::list<int>>& adj, std::vector<std::vector<int>> components) {

    std::vector<std::vector<int>> allCycles;

    for (auto each : components) {
        std::map<int,int> numEdges;
    
        for (unsigned i = 0; i < adj.size(); i++) {
            numEdges[i] = adj[i].size();
        }
    
        if (!adj.size()) {
            allCycles.push_back(std::vector<int>());
        }
    
        std::stack<int> path;
    
        std::vector<int> cycle;
    
        path.push(each[0]);
        int curr = each[0];
    
        while (!path.empty()) {
            if (numEdges[curr]) {
                path.push(curr);
    
                int next = adj[curr].back();
    
                numEdges[curr]--;
                adj[curr].pop_back();

                curr = next;
            } else {
                cycle.push_back(curr);
    
                curr = path.top();
                path.pop();
            }
        }
    
        reverse(cycle.begin(), cycle.end());
        allCycles.push_back(cycle);
    }
    
    return allCycles;
}

std::vector<std::list<int>> makeEulerianAdj(Graph g, std::vector<int> component) {
    std::vector<std::list<int>> adj;
    for (auto each : component) {
        adj.push_back(g.out_neighbors(each));
    }
    return adj;
}

