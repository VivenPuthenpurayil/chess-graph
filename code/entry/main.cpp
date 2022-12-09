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
    // Parse 500 games
    std::ifstream file("../../data/carlsen_preprocessed.txt");

    std::vector<float> evaluation;
    std::vector<std::vector<float>> characteristics;
    
    std::vector<float> positionCharacteristics;

    const int num_positions = 2000;

    for (int i = 0; i < num_positions; i++) {
        std::string line;
        std::getline(file, line);

        std::vector<std::string> data;
        SplitString(line, ',', data);

        Position pos(data);

        evaluation.push_back(pos.evaluation / 100);
        
        Graph b_support = generateSupport(pos, DARK);
        Graph w_support = generateSupport(pos, LIGHT);

        Graph b_attack = generateAttack(pos, DARK);
        Graph w_attack = generateAttack(pos, LIGHT);

        Graph w_position = Graph::g_union(w_support, w_attack);
        Graph b_position = Graph::g_union(b_support, b_attack);

        //if (std::abs(pos.material_white - pos.material_black) > 2 ) {
        //   continue;
        //}

        // Calculate Characteristics
        float white;
        float black;

        // Material Difference (SANITY CHECK EHRE)
        white = pos.material_white;
        black = pos.material_black;
        positionCharacteristics.push_back(white - black);

        // Average Support Degree
        white = average_degree(w_support);
        black = average_degree(b_support);

        positionCharacteristics.push_back(white - black);

        // Average Attack Degree
        white = average_degree(w_attack);
        black = average_degree(b_attack);

        positionCharacteristics.push_back(white - black);

        // Average Position Degree
        white = average_degree(w_position);
        black = average_degree(b_position);

        positionCharacteristics.push_back(white - black);

        // Now do SCCS
        std::vector<int> white_ll(64); // White lowlink
        std::vector<int> black_ll(64); // Black lowlink

        // Support
        white_ll = tarjans(w_support);
        black_ll = tarjans(b_support);

        white = max_size_scc(white_ll);
        black = max_size_scc(black_ll);

        positionCharacteristics.push_back(white - black);

        for (int k = 0; k < 6; k++) {
            white = num_large_scc(white_ll, k);
            black = num_large_scc(black_ll, k);

            positionCharacteristics.push_back(white - black);
        }

        // Attack
        /**
        white_ll = tarjans(w_attack);
        black_ll = tarjans(b_attack);

        white = max_size_scc(white_ll);
        black = max_size_scc(black_ll);

        std::cout << white-black << " ";

        positionCharacteristics.push_back(white - black);

        for (int k = 0; k < 6; k++) {
            white = num_large_scc(white_ll, k);
            black = num_large_scc(black_ll, k);

            positionCharacteristics.push_back(white - black);
        }
        */


        // Position
        white_ll = tarjans(w_position);
        black_ll = tarjans(b_position);

        white = max_size_scc(white_ll);
        black = max_size_scc(black_ll);

        positionCharacteristics.push_back(white - black);

        for (int k = 0; k < 6; k++) {
            white = num_large_scc(white_ll, k);
            black = num_large_scc(black_ll, k);

            positionCharacteristics.push_back(white - black);
        }

       



        // Add the entire characterstics of the graph to the thing.
        characteristics.push_back(positionCharacteristics);
        positionCharacteristics.clear();



        /**
        float white = max_size_scc(tarjans(w_support)); //num_large_scc(tarjans(w_support), 4);
        float black = max_size_scc(tarjans(b_support)); //num_large_scc(tarjans(b_support), 4);
        white = w_support.num_edges();
        black = b_support.num_edges();
        white = average_degree(w_support);
        black = average_degree(b_support);
        //
        */

        //std::cout << white - black << ", " << pos.evaluation - (100 * (pos.material_white - pos.material_black));
        /**for (auto & g : graphs) {
            std::vector<int> ll(pos.num_pieces);
            ll = tarjans(g);
            int sccs = num_large_scc(ll, 1);
            int edges = g.num_edges();
            std::cout << sccs << " ";
        }
        */
       
        
    }

    // Run + Output Linear Regression Results
    // Loop through the characteristics for the first position.
    for (int i = 0; i < (int) characteristics[0].size(); i++) {
        std::vector<float> characteristic; // Representing one characteristic for all positions
        for (int j = 0; j < num_positions; j++) {
            characteristic.push_back(characteristics[j][i]);
        }
        float r2 = LinearRegression(characteristic, evaluation);

        std::cout << r2 << " " << LinearRegression(evaluation, characteristic) << "\n";
    }
    
    file.close();

    return 0;
}