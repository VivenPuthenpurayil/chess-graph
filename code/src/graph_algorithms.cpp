#include "graph_algorithms.h"

// Receive input of a graph
// Output a map of each vertex that maps to its own centrality
std::map<int, int> brandes(const Graph& g) {
    //initialize map to return
    std::map<int, int> c;
    // populating map with 0 values for initial state
    for (int v = 0; v < g.num_verticies(); v++) {
        c[v] = 0;
    }
    // Iterate for each vertex in map
    for (int v = 0; v < g.num_verticies(); v++) {
        std::stack<int> s;
        std::map<int, std::vector<int>> p;
        std::map<int, int> ge;
        std::map<int, int> d;
        
        // populate each map
        // p is a map of vertices to optimal pathways

        for (int a = 0; a < g.num_verticies(); a++) {
            p[a] = std::vector<int>();
            ge[a] = 0;
            d[a] = -1;
        }
        // set initial state for node currently being visisted 
        ge[v] = 1;
        d[v] = 0;

        std::queue<int> q;
        q.push(v);
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            s.push(curr);
            std::list<int> w1 = g.neighbors(curr);

            for (int w : w1) {
                //check if the node is being visited for the first time
                if (d[w] < 0) {
                    q.push(w);
                    d[w] = d[curr] + 1;
                }
                //shortest path from w to curr
                if (d[w] == d[curr] + 1) {
                    ge[w] = ge[w] + ge[curr];
                    p[w].push_back(curr);
                }
            }
        }

        std::map<int, int> e;

        //return vertices in order of non -increasing distance from s
        for (int a = 0; a < g.num_verticies(); a++) {
            e[a] = 0;
        }

        while (!s.empty())
        {
            int w = s.top();
            s.pop();
            for (int ve : p[w])
            {
                e[ve] = e[ve] + (ge[ve] / ge[w]) * (1 + e[w]);
            }
            if (w != v)
            {
                c[w] = c[w] + e[w];
            }
        }
    }
    return c;
}

//Input graph g
//Output float representing the average degree
float average_degree(const Graph& g) {
    return ((float) g.num_edges()) / ((float) g.num_verticies()) * 2;
}

//Input graph g
//Output integer representing the max degree
int max_degree(const Graph& g) {
    int max = 0;
    for (int i = 0; i < g.num_verticies(); i++)
    {
        if (g.degree(i) > max)
        {
            max = g.degree(i);
        }
    }
    return max;
}

//Input vector of lowlinks
//Output integer representin size of larges strongly connected components
int max_size_scc(std::vector<int> lowlink) {

    std::map<int, int> sizes;
    for (int i : lowlink)
    {
        sizes[i]++;
    }

    int max_size = std::max_element(sizes.begin(), sizes.end(),
                                    [](const std::pair<int, int> &p1, const std::pair<int, int> &p2)
                                    { return p1.second < p2.second; })
                       ->second;

    return max_size;
}


//Input vector representing lowlinks
//Output intger representing the number of strongly connected components
int num_scc(std::vector<int> lowlink) {
    int s = (int) lowlink.size();

    std::sort(lowlink.begin(), lowlink.end());
    auto last = std::unique(lowlink.begin(), lowlink.end());
    lowlink.resize(std::distance(lowlink.begin(), last));

    return lowlink.size();
}

//Input vector representing lowlinks and integer for size
//Output integer representing number of large strongly connected components
int num_large_scc(std::vector<int> lowlink, int size) {
    int s = (int) lowlink.size();

    std::sort(lowlink.begin(), lowlink.end());

    int limit = size; // How big the sccs have to be

    int curr = lowlink[0];
    int count = 0;
    int out = 0;

    for (int i : lowlink)
    {
        if (curr == i)
        {
            count++;
        }
        else if (curr != i)
        {
            if (count > limit)
            {
                out++;
            }
            curr = i;
            count = 1;
        }
    }
    if (count > limit)
    {
        out++;
    }
    return out;
}

std::vector<int> purge_small_ll(std::vector<int> lowlink, int size)
{
    // Replace the sccs that are too small with -1;
    int s = (int)lowlink.size();

    int limit = size; // How big the sccs have to be

    int curr = lowlink[0];
    int count = 0;
    std::vector<int> survivors(s, 0);

    for (int i : lowlink)
    {
        if (i == -1)
        {
            continue;
        }
        survivors[i]++;
    }
    for (int i = 0; i < s; i++)
    {
        if (lowlink[i] == -1)
        {
            continue;
        }
        // Not greater than the limit
        if (survivors[lowlink[i]] <= limit)
        {
            lowlink[i] = -1;
        }
    }
    return lowlink;
}

//Input Graph g
//Output vector of integers of lowlinks
std::vector<int> tarjans(const Graph& g) {

    int size = g.num_verticies();
    int count = 0;
    int id = 0;

    // For Tarjans
    std::vector<int> lowlink(size, 0); // Store low link values of each node
    std::stack<int> ll_stack;          // store if they are on the tarjans stack
    std::vector<bool> on_stack(size, false);
    std::vector<int> ids(size, 0);

    // For our DFS
    std::vector<bool> visited(size, false);

    for (int i = 0; i < size; i++)
    {
        // Make sure we get every connected component
        if (visited[i] == true)
        {
            continue;
        }
        tarjans_(i, g, lowlink, ll_stack, on_stack, visited, id, ids);
    }
    return lowlink;
}


void tarjans_(int v, const Graph &g, std::vector<int> &lowlink, std::stack<int> &ll_stack, std::vector<bool> &on_stack, std::vector<bool> &visited, int &id, std::vector<int> &ids)
{
    ll_stack.push(v);
    on_stack[v] = true;
    visited[v] = true;
    lowlink[v] = id;
    ids[v] = id++;

    for (int n : g.out_neighbors(v))
    {
        if (visited[n] == false)
        {
            tarjans_(n, g, lowlink, ll_stack, on_stack, visited, id, ids);
        }
        if (on_stack[n] == true)
        {
            lowlink[v] = std::min(lowlink[v], lowlink[n]);
        }
    }

    if (lowlink[v] == ids[v])
    {
        while (!ll_stack.empty())
        {
            int i = ll_stack.top();
            ll_stack.pop();
            lowlink[i] = ids[v];
            on_stack[i] = false;
            if (i == v)
            {
                break;
            }
        }
    }
}

int count_hanging_pieces(const Graph &attack, const Graph &support)
{
    int num = 0;
    for (int i = 0; i < attack.num_verticies(); i++)
    {
        if (attack.in_degree(i) > 0)
        { // Pieces under attack
            if (support.in_degree(i) < attack.in_degree(i))
            {
                num++; // The piece is hanging
            }
        }
    }
    return num;
}

int count_undefended_defenders(const Graph &support)
{
    int num = 0;
    for (int i = 0; i < support.num_verticies(); i++)
    {
        if ((support.getLabel(i) != 0 && support.in_degree(i) < 1))
        { // There is a piece here for this graph
            num++;
        }
    }
    return num;
}

//Input of graph g
//Output of a vector of vector of integers representing each weakly connected component
std::vector<std::vector<int>> weaklyconnected(const Graph& g){  //might need undirected
    //creates a return graph of weakly connected components
    std::vector<std::vector<int>> components;
    unsigned size = g.num_verticies();
    std::vector<bool> visited(size,false);
    //iterates through each node in graph
    for(unsigned i=0;i<size;i++){
        if(!visited[i]){
            //if a node is not visited, create a new connected component and find connections recursively
            std::vector<int> c;
            findConnected(i, visited, c, g);
            for (auto i : c)
            {
            }
            if (!c.empty()) {
                //push nodes into components vector
                components.push_back(c);
            }
        }
    }
    return components;
}

//Input of current node, vector of visited nodes, empty vector for current connected component, graph g
//Output None
void findConnected(int node, std::vector<bool>& visited, std::vector<int>& component, Graph g){
    //sets input node to visited
    visited[node] = true;
    //pushes node to vector of components of current weakly connected component
    component.push_back(node);
    for(auto i:g.neighbors(node)){
        //recursively checks if each neighbor is visited
        if(!(visited[i])){
            findConnected(i,visited,component,g);
        }
    }
}

//Input graph g and vector of weakly connected components
//Output of 2D vector where each vector represents a eulerian cycle
std::vector<std::vector<int>> eulerian(Graph g, std::vector<std::vector<int>> components) {

    std::vector<std::vector<int>> allCycles;

    //finds the number of edges to help find unused edges
    for (unsigned i = 0; i < components.size(); i++) {
        std::map<int,int> numEdges;
        std::vector<std::list<int>> adj = makeEulerianAdj(g, components[i]);

        for (unsigned i = 0; i < adj.size(); i++)
        {
            numEdges[i] = adj[i].size();
        }

        if (!adj.size()) {
            allCycles.push_back(std::vector<int>());
            break;
        }

        //stack to hold vertices
        std::stack<int> path;
        //stores current cycle
        std::vector<int> cycle;

        path.push(components[i][0]);
        int curr = components[i][0];
        int first = components[i][0];
    
        while (!path.empty()) {
            //check if there are any edges left
            if (numEdges[curr-first]) {
                //push vertex
                path.push(curr);

                //find next vertex 
                int next = adj[curr-first].back();

                //remove edge just used
                numEdges[curr-first]--;
                adj[curr-first].pop_back();

                //incr vertices
                curr = next;
            
            //backtracking portion to find next cycle
            } else {
                cycle.push_back(curr);

                curr = path.top();
                path.pop();
            }
        }

        std::vector<std::list<int>> adjFull = makeEulerianAdj(g, components[i]);

        // Getting the number of edges in graph
        int nEdges = 0;
        for (int x = 0; x < (int)adjFull.size(); x++) {
            nEdges += adjFull[x].size();
        }

        // Checking to see if the output is a valid eulerian cycle
        if (cycle.front() != cycle.back() || cycle.size() != (unsigned)(nEdges + 1)) {
            allCycles.push_back(std::vector<int>());
        } else {
            reverse(cycle.begin(), cycle.end());
            allCycles.push_back(cycle);
        }
    }

    return allCycles;
}

// Input a graph and a vector of ints of one weakly connected component
// Output of a vector of a list of ints which is an adjacency list
std::vector<std::list<int>> makeEulerianAdj(Graph g, std::vector<int> component)
{
    std::vector<std::list<int>> adj;
    for (auto each : component)
    {
        adj.push_back(g.out_neighbors(each));
    }
    return adj;
}

// Input a graph
// Outputs the total number of cycles that occurs in each of the graphs weakly connected components
int numCycles(Graph g) {
    std::vector<std::vector<int>> components = weaklyconnected(g);

    std::vector<std::vector<int>> eul = eulerian(g, components);

    int cycles = 0;
    for (auto each : eul)
    {
        if (!each.empty())
        {
            cycles++;
        }
    }

    return cycles;
}
