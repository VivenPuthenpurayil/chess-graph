#include "brandes.h"
#include <queue>
#include <stack>

std::map<int, int> brandes(const Graph& g) {
    std::map<int, int> c;
    for (int v = 0; v < g.num_verticies(); v++) {
        c[v] = 0;
    }
    for (int v = 0; v < g.num_verticies(); v++) {
        std::stack<int> s;
        std::map<int, std::vector<int>> p;
        std::map<int, int> ge;
        std::map<int, int> d;
        for (int a = 0; a < g.num_verticies(); a++) {
            p[a] = std::vector<int>();
            ge[a] = 0;
            d[a] = -1;
        }
        ge[v] = 1;
        d[v] = 0;   

        std::queue<int> q;
        q.push(v);
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            s.push(curr);
            std::list<int> w1 = g.neighbors(curr);
            for (int w : w1) {
                if (d[w] < 0) {
                    q.push(w);
                    d[w] = d[curr] + 1;
                }
                if (d[w] == d[curr] + 1) {
                    ge[w] = ge[w] + ge[curr];
                    p[w].push_back(curr);
                }
            }
        }

        std::map<int, int> e;
        for (int a = 0; a < g.num_verticies(); a++) {
            e[a] = 0;
        }

        while (!s.empty()) {
            int w = s.top();
            s.pop();
            for (int ve : p[w]) {
                e[ve] = e[ve] + (ge[ve]/ge[w]) * (1+e[w]);
            }
            if ( w != v ) {
                c[w] = c[w] + e[w];
            }
        }
    
    }
    return c;
}