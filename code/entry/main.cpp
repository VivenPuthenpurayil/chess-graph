#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "utils.h"
#include "position.h"
#include "graph.h"
#include "graph_algorithms.h"
#include "graph_generator.h"

int main()
{
    // Parse 50 games
    std::ifstream file("../../data/preprocessed.txt");
    
    for (int i = 0; i < 50; i++) {
        std::string line;
        std::getline(file, line);

        std::vector<std::string> data;
        SplitString(line, ',', data);

        Position pos(data);
        

        Graph b_support = generateSupport(pos, DARK);
        Graph w_support = generateSupport(pos, LIGHT);
        Graph b_attack = generateAttack(pos, DARK);
        Graph w_attack = generateAttack(pos, LIGHT);

        std::list<Graph> graphs;
        graphs.push_back(b_support);
        graphs.push_back(w_support);
        graphs.push_back(b_attack);
        graphs.push_back(w_attack);
        std::cout << "Graph #" << i << ": ";

        for (auto & g : graphs) {
            std::vector<int> ll(pos.num_pieces);
            ll = tarjans(g);
            int sccs = num_scc(ll);
            int edges = g.num_edges();
            std::cout << edges << " ";
        }
        std::cout << "\n";
        
    }

    file.close();


    return 0;
}