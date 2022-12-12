#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "utils.h"
#include "position.h"
#include "graph.h"
#include "graph_algorithms.h"
#include "graph_generator.h"

int main(int argc, char **argv)
{
    // Parse 500 games
    InputParser input(argc, argv);
    int num_positions = 0;

    if (!input.cmdOptionExists("-n")) {
        std::cerr << "Please specify number of positions to analyze using -n" << std::endl;
        return 1;
    }
    else {
        num_positions = std::stoi(input.getCmdOption("-n"));
    }

    std::ifstream infile;
    std::ofstream outfile;

    if (!input.cmdOptionExists("-i")) {
        std::cerr << "Please specify input file using -i" << std::endl;
        return 1;
    }
    else {
        std::string path = input.getCmdOption("-i");
        infile.open(path);
    }

    if (input.cmdOptionExists("-o")) {
        std::string path = input.getCmdOption("-o");
        outfile.open(path);
    }
    else {
        outfile.open("../../output/out.txt");
    }

    

    std::vector<float> evaluation;
    std::vector<int> result;
    std::vector<std::vector<float>> characteristics;

    std::vector<bool> whiteWinBrandes;
    std::vector<bool> whiteWinBrandes2;
    std::vector<bool> whiteMaterial;
    std::vector<bool> whiteEdge;
    std::vector<bool> whiteEdge2;


    
    std::vector<float> positionCharacteristics;

    
    outfile << " Graph # |" << " Result |" << " Evaluation |" << " Characteristics" << "\n"; // Label characteristics later;
    for (int i = 0; i < num_positions; i++) {
        outfile << i + 1 << ","; // Graph Number

        std::string line;
        std::getline(infile, line);

        std::vector<std::string> data;
        SplitString(line, ',', data);

        Position pos(data);

        evaluation.push_back(pos.evaluation / 100);
        result.push_back(pos.result);
        outfile << pos.result << "," << pos.evaluation / 100 << ",";
        
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

        whiteMaterial.push_back(white > black);



        positionCharacteristics.push_back(white - black);
    
    std::map<int, int> whitec = brandes(w_support);
    std::map<int, int> blackc = brandes(b_support);

    int whitem = 0;
    int blackm = 0;
    int whitem2 = 0;
    int blackm2 = 0;

    for (auto w: whitec) {
        whitem += w.second;
        if (w.second > whitem2) {
            whitem2 = w.second;
        }
    }
    for (auto b: blackc) {
        blackm += b.second;
        if (b.second > blackm2) {
            blackm2 = b.second;
        }
    }


    whiteWinBrandes.push_back(whitem >= blackm);
    whiteWinBrandes2.push_back(whitem2 >= blackm2);

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

        // Number of edges
        white = w_support.num_edges();
        black = b_support.num_edges();
        positionCharacteristics.push_back(white - black);
        whiteEdge.push_back((white - black) > 0);

        white = w_attack.num_edges();
        black = b_attack.num_edges();
        positionCharacteristics.push_back(white - black);

        white = w_position.num_edges();
        black = b_position.num_edges();
        positionCharacteristics.push_back(white - black);
        whiteEdge2.push_back((white - black) > 0);


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

        for (auto c : positionCharacteristics) {
            outfile << c << ",";
        }
        outfile << std::endl;
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

    //std::vector<float> analysis_vec = evaluation;
    std::vector<float> result2(result.begin(), result.end());

    for (int i = 0; i < (int) characteristics[0].size(); i++) {
        std::vector<float> characteristic; // Representing one characteristic for all positions
        for (int j = 0; j < num_positions; j++) {
            characteristic.push_back(characteristics[j][i]);
        }
        float eval_r2 = LinearRegression(characteristic, evaluation);
        float result_r2 = LinearRegression(characteristic, result2);

        std::cout << eval_r2 << " " << result_r2 << "\n";
    }
    
    infile.close();
    outfile.close();
    int correct = 0;
    int correct2 = 0;
    int correct3 = 0;
    int correct4 = 0;
    int correct5 = 0;

    for (unsigned i = 0; i < whiteWinBrandes.size(); i++) {
        if (result[i] == 1 && whiteWinBrandes[i]) {
            correct += 1;
        }
        if (result[i] == 0 && !whiteWinBrandes[i]) {
            correct += 1;
        } 
        if (result[i] == 1 && whiteWinBrandes2[i]) {
            correct2 += 1;
        }
        if (result[i] == 0 && !whiteWinBrandes2[i]) {
            correct2 += 1;
        }


        if (result[i] == 1 && whiteMaterial[i]) {
            correct3 += 1;
        }
        if (result[i] == 0 && !whiteMaterial[i]) {
            correct3 += 1;
        }   

        if (result[i] == 1 && whiteEdge[i]) {
            correct4 += 1;
        }
        if (result[i] == 0 && !whiteEdge[i]) {
            correct4 += 1;
        }

        if (result[i] == 1 && whiteEdge2[i]) {
            correct5 += 1;
        }
        if (result[i] == 0 && !whiteEdge2[i]) {
            correct5 += 1;
        }             
    }
    std::cout << "The total amount correct predictions is: " << correct << " out of " << whiteWinBrandes.size() << " guesses giving a accuracy rate of: " << (float)(correct)/ (float)(whiteWinBrandes.size()) << std::endl;
    std::cout << "The total amount correct predictions is: " << correct2 << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(correct2)/ (float)(whiteWinBrandes.size()) << std::endl;
    std::cout << "The total amount correct predictions is: " << correct3 << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(correct3)/ (float)(whiteWinBrandes.size()) << std::endl;
    std::cout << "The total amount correct predictions is: " << correct4 << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(correct4)/ (float)(whiteWinBrandes.size()) << std::endl;
    std::cout << "The total amount correct predictions is: " << correct5 << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(correct5)/ (float)(whiteWinBrandes.size()) << std::endl;


    return 0;
}