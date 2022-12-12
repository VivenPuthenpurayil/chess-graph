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

    if (!input.cmdOptionExists("-n"))
    {
        std::cerr << "Please specify number of positions to analyze using -n" << std::endl;
        return 1;
    }
    else
    {
        num_positions = std::stoi(input.getCmdOption("-n"));
    }

    std::ifstream infile;
    std::ofstream outfile;

    if (!input.cmdOptionExists("-i"))
    {
        std::cerr << "Please specify input file using -i" << std::endl;
        return 1;
    }
    else
    {
        std::string path = input.getCmdOption("-i");
        infile.open(path);
    }

    if (input.cmdOptionExists("-o"))
    {
        std::string path = input.getCmdOption("-o");
        outfile.open(path);
    }
    else
    {
        outfile.open("../../output/out.txt");
    }

    std::vector<float> evaluation;
    std::vector<float> result;
    std::vector<std::vector<float>> characteristics;


    // set up vectors for predicting if white wins based on different functions
    std::vector<bool> whiteWinBrandes;
    std::vector<bool> whiteWinBrandes2;
    std::vector<bool> whiteMaterial;
    std::vector<bool> whiteEdge;
    std::vector<bool> whiteEdge2;
    std::vector<bool> eulerianPredictor;
    std::vector<bool> tarjanPredcitor;

    std::vector<float> positionCharacteristics;

    outfile << " Graph # |"
            << " Result |"
            << " Evaluation |"
            << " Characteristics"
            << "\n"; // Label characteristics later;
    for (int i = 0; i < num_positions; i++)
    {
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

        // if (std::abs(pos.material_white - pos.material_black) > 2 ) {
        //    continue;
        // }

        // Calculate Characteristics
        float white;
        float black;

        // Material Difference (SANITY CHECK EHRE)
        white = pos.material_white;
        black = pos.material_black;


        // true if white has more material than black
        whiteMaterial.push_back(white > black);

        positionCharacteristics.push_back(white - black);

        white = numCycles(w_position);
        black = numCycles(b_position);

        positionCharacteristics.push_back(white - black);

        white = numCycles(w_support);
        black = numCycles(b_support);

        positionCharacteristics.push_back(white - black);


        //calculate the amount of cycles in each support graph
        int wE = numCycles(w_support);
        int bE = numCycles(b_support);
        // if white has more eulerian cycles, we predict it loses
        eulerianPredictor.push_back(wE <= bE);


        // run brandes on both attack graphs
        std::map<int, int> whitec = brandes(w_attack);
        std::map<int, int> blackc = brandes(b_attack);


        // set variables to keep track of maximum values and totals for centrality
        int whitem = 0;
        int blackm = 0;
        int whitem2 = 0;
        int blackm2 = 0;


        //loop to find and evaluate
        for (auto w : whitec)
        {
            whitem += w.second;
            if (w.second > whitem2)
            {
                whitem2 = w.second;
            }
        }
        for (auto b : blackc)
        {
            blackm += b.second;
            if (b.second > blackm2)
            {
                blackm2 = b.second;
            }
        }

        // white wins either condition if it has a greater value.
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

        //predict white wins if it has more edges than black
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


        // predict white wins with more strongly connected components
        tarjanPredcitor.push_back((white - black) > 0);
        positionCharacteristics.push_back(white - black);

        for (int k = 0; k < 6; k++)
        {
            white = num_large_scc(white_ll, k);
            black = num_large_scc(black_ll, k);

            positionCharacteristics.push_back(white - black);
        }

        // Position
        white_ll = tarjans(w_position);
        black_ll = tarjans(b_position);

        white = max_size_scc(white_ll);
        black = max_size_scc(black_ll);

        positionCharacteristics.push_back(white - black);

        for (int k = 0; k < 6; k++)
        {
            white = num_large_scc(white_ll, k);
            black = num_large_scc(black_ll, k);

            positionCharacteristics.push_back(white - black);
        }

        // Add the entire characterstics of the graph to the thing.
        characteristics.push_back(positionCharacteristics);

        for (auto c : positionCharacteristics)
        {
            outfile << c << ",";
        }
        outfile << std::endl;
        positionCharacteristics.clear();
    }

    // Run + Output Linear Regression Results
    // Loop through the characteristics for the first position.

    std::vector<float> result2(result.begin(), result.end());

    for (int i = 0; i < (int)characteristics[0].size(); i++)
    {
        std::vector<float> characteristic; // Representing one characteristic for all positions
        for (int j = 0; j < num_positions; j++)
        {
            characteristic.push_back(characteristics[j][i]);
        }
        float eval_r2 = LinearRegression(characteristic, evaluation);
        float result_r2 = LinearRegression(characteristic, result2);
    }

    infile.close();
    outfile.close();

    // initialize values to count correct attempts 
    int centralityTotalPredictorSum = 0;
    int centralityMaxPredictorSum = 0;
    int materialPredictorSum = 0;
    int edgePredictorSupportSum = 0;
    int edgePredictorPositionSum = 0;
    int eulerianPredictorSum = 0;
    int tarjanPredictorSum = 0;
    int aggregate = 0;

    // iterate through all vectors to calculate accuracy
    for (unsigned i = 0; i < whiteWinBrandes.size(); i++)
    {
        // initialize value to aggregate predictors -- currently using equal weights for all predictors
        int sub = 0;
        if (whiteWinBrandes[i])
        {
            sub += 1;
        }
        if (whiteWinBrandes2[i])
        {
            sub += 1;
        }

        if (whiteEdge[i])
        {
            sub += 2;
        }

        if (whiteEdge2[i])
        {
            sub += 2;
        }

        if (eulerianPredictor[i])
        {
            sub += 2;
        }

        // establishing condition to count aggregated value as a win or loss for whtie
        bool res = sub >= 3;

        // checking accross all values to see if they predict accurately
        if ((result[i] == 1 && whiteWinBrandes[i]) || (result[i] == 0 && !whiteWinBrandes[i]))
        {
            centralityTotalPredictorSum += 1;
        }
        if ((result[i] == 1 && tarjanPredcitor[i]) || (result[i] == 0 && !tarjanPredcitor[i]))
        {
            tarjanPredictorSum += 1;
        }

        if ((result[i] == 1 && whiteWinBrandes2[i]) || (result[i] == 0 && !whiteWinBrandes2[i]))
        {
            centralityMaxPredictorSum += 1;
        }

        if ((result[i] == 1 && whiteMaterial[i]) || (result[i] == 0 && !whiteMaterial[i]))
        {
            materialPredictorSum += 1;
        }

        if ((result[i] == 1 && whiteEdge[i]) || (result[i] == 0 && !whiteEdge[i]))
        {
            edgePredictorSupportSum += 1;
        }

        if ((result[i] == 1 && whiteEdge2[i]) || (result[i] == 0 && !whiteEdge2[i]))
        {
            edgePredictorPositionSum += 1;
        }

        if ((result[i] == 1 && eulerianPredictor[i]) || (result[i] == 0 && !eulerianPredictor[i]))
        {
            eulerianPredictorSum += 1;
        }

        if ((result[i] == 1 && res )|| (result[i] == 0 && !res))
        {
            aggregate += 1;
        }

    }

    // print results
    std::cout << "The centralityTotalPredictorSum predictions is: " << centralityTotalPredictorSum << " out of " << whiteWinBrandes.size() << " guesses giving a accuracy rate of: " << (float)(centralityTotalPredictorSum) / (float)(whiteWinBrandes.size()) << std::endl;
    std::cout << "The centralityMaxPredictorSum predictions is: " << centralityMaxPredictorSum << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(centralityMaxPredictorSum) / (float)(whiteWinBrandes.size()) << std::endl;
    std::cout << "The materialPredictorSum predictions is: " << materialPredictorSum << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(materialPredictorSum) / (float)(whiteWinBrandes.size()) << std::endl;
    std::cout << "The edgePredictorSupportSum predictions is: " << edgePredictorSupportSum << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(edgePredictorSupportSum) / (float)(whiteWinBrandes.size()) << std::endl;
    std::cout << "The edgePredictorPositionSum predictions is: " << edgePredictorPositionSum << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(edgePredictorPositionSum) / (float)(whiteWinBrandes.size()) << std::endl;
    std::cout << "The eulerianPredictorSum predictions is: " << eulerianPredictorSum << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(eulerianPredictorSum) / (float)(whiteWinBrandes.size()) << std::endl;
    std::cout << "The tarjanPredictorSum predictions is: " << tarjanPredictorSum << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(tarjanPredictorSum) / (float)(whiteWinBrandes.size()) << std::endl;


    std::cout << "The aggregate predictions is: " << aggregate << " out of " << whiteWinBrandes2.size() << " guesses giving a accuracy rate of: " << (float)(aggregate) / (float)(whiteWinBrandes.size()) << std::endl;

    return 0;
}