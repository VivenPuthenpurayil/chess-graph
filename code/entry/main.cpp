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
    
    for (int i = 0; i < 500; i++) {
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
        //graphs.push_back(b_attack);
        //graphs.push_back(w_attack);
        std::cout << "Graph #" << i+1 << ", ";
        int white = max_size_scc(tarjans(w_support)); //num_large_scc(tarjans(w_support), 4);
        int black = max_size_scc(tarjans(b_support)); //num_large_scc(tarjans(b_support), 4);
        std::cout << white - black << ", " << pos.evaluation;
        /**for (auto & g : graphs) {
            std::vector<int> ll(pos.num_pieces);
            ll = tarjans(g);
            int sccs = num_large_scc(ll, 1);
            int edges = g.num_edges();
            std::cout << sccs << " ";
        }
        */
        std::cout << "\n";
        
    }

    file.close();


    return 0;
}