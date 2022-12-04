#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "utils.h"
#include "position.h"
#include "graph.h"
#include "graph_algorithms.h"
#include "graph_generator.h"
#include "visualizer.h"

int main() {
    // Read in first line of our test data
    std::ifstream file("../../data/preprocessed.txt");

    for (int i = 0; i < 500; i++) {
        std::string line;
        std::getline(file, line);

        std::vector<std::string> data;
        SplitString(line, ',', data);

        // Build position from data
        
        Position p(data);
        Graph g = generateSupport(p, LIGHT);
        int scc_count = num_large_scc(tarjans(g), 1);
        int max_scc = max_size_scc(tarjans(g));
        std::vector<int> colorscheme = purge_small_ll(tarjans(g), 1);

        std::cout << "Graph #" << i+1 << ", " << scc_count << " " << max_scc << "\n";
        display_groups(p, colorscheme);

    }
        
    
    

    
    

}