#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "../lib/cs225/Image.h"
#include "../lib/cs225/StickerSheet.h"

#include "utils.h"
#include "position.h"
#include "graph.h"
#include "graph_algorithms.h"
#include "graph_generator.h"
#include "visualizer.h"

/**
 * Command line options / flags
 * -n [number] -o [outfolder] -g [attack|support|position] -c [black|white|both]
*/
int main(int argc, char **argv) {
    // Read in first line of our test data
    InputParser input(argc, argv);

    std::ifstream file("../../data/preprocessed.txt");

    if (!input.cmdOptionExists("-n")) {
        std::cerr << "Please specify number of positions using -n" << std::endl;
        return 1;
    }

    int n = stoi(input.getCmdOption("-n"));

    Image output;
    std::string outfolder;
    std::string outfile;
    
    if (input.cmdOptionExists("-o")) {
        outfolder = input.getCmdOption("-o");
    }
    else {
        outfolder = "../output/";
    }
    
    // Default values
    std::string graph_option = "support";
    std::string color_option = "white";

    if (input.cmdOptionExists("-g")) {
        graph_option = input.getCmdOption("-g");
    }

    if (input.cmdOptionExists("-c")) {
        color_option = input.getCmdOption("-c");
    }

    for (int i = 0; i < n; i++) {
        std::string line;
        std::getline(file, line);

        std::vector<std::string> data;
        SplitString(line, ',', data);

        // Build position from data
        Position p(data);

        Graph white_support = generateSupport(p, LIGHT);
        Graph black_support = generateSupport(p, DARK);
        Graph union_support = Graph::g_union(white_support, black_support);
    
        Graph white_attack = generateAttack(p, LIGHT);
        Graph black_attack = generateAttack(p, DARK);
        Graph union_attack = Graph::g_union(white_attack, black_attack);

        Graph white_position = Graph::g_union(white_support, white_attack);
        Graph black_position = Graph::g_union(black_support, black_attack);
        

        /*
        int scc_count = num_large_scc(tarjans(union_support), 1);
        int max_scc = max_size_scc(tarjans(union_support));
        std::vector<int> colorscheme = purge_small_ll(tarjans(union_support), 1);

        std::cout << "Graph #" << i+1 << ", " << scc_count << " " << max_scc << "\n";
        display_groups(p, colorscheme);

        Image output = get_groups_image(p, colorscheme);
        string outfile = "../output/scc" + std::to_string(i) + ".png"; 
        output.writeToFile(outfile);


        
        output = get_position_image(p);
        draw_edges(white_attack, output, 0); // Red white attack edges
        draw_edges(black_attack, output, 100); // Green black attack edges
        outfile = "../output/attack" + std::to_string(i) + ".png"; 
        output.writeToFile(outfile);

        output = get_position_image(p);
        draw_edges(white_support, output, 0);
        draw_edges(black_support, output, 100);
        outfile = "../output/support" + std::to_string(i) + ".png"; 
        output.writeToFile(outfile);

        */
        output.readFromFile("../../images/chessboard.png");
        draw_edges(white_support, output, 0);
        draw_edges(black_support, output, 240);
        draw_edges(white_attack, output, 60); // Red white attack edges
        draw_edges(black_attack, output, 180);
        draw_position(p, output);
        outfile = outfolder + "position" + std::to_string(i) + ".png"; 
        output.writeToFile(outfile);




    }

    return 0;
        
}