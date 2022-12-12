#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "graph.h"
#include "position.h"
#include "graph_generator.h"
#include "graph_algorithms.h"
#include "../lib/cs225/Image.h"
#include "../lib/cs225/StickerSheet.h"
#include "visualizer.h"

#define LIGHT 1
#define DARK 0

using namespace std;

TEST_CASE("test Misc::hanging pieces")
{
	Position default_pos; 
    Graph w_support = generateSupport(default_pos, LIGHT);
    Graph b_support = generateSupport(default_pos, DARK);

    Graph w_attack = generateAttack(default_pos, LIGHT);
    Graph b_attack = generateAttack(default_pos, DARK);
	
	REQUIRE(count_hanging_pieces(w_attack, b_support) == 0);
    REQUIRE(count_hanging_pieces(b_attack, w_support) == 0);

    REQUIRE(count_undefended_defenders(w_support) == 2); // Rooks are undefended
    REQUIRE(count_undefended_defenders(b_support) == 2); // Rooks are undefended


}

TEST_CASE("test SANITY")
{
    Position default_pos;
    Graph w_support = generateSupport(default_pos, LIGHT);
    Graph b_support = generateSupport(default_pos, DARK);

    Graph w_attack = generateAttack(default_pos, LIGHT);
    Graph b_attack = generateAttack(default_pos, DARK);

    Graph w_position = Graph::g_union(w_support, w_attack);
    Graph b_position = Graph::g_union(b_support, b_attack);

    Image output;
    output.readFromFile("../../images/chessboard.png");
    draw_edges(w_support, output, 0);
    draw_edges(b_support, output, 240);
    draw_edges(w_attack, output, 60); // Red white attack edges
    draw_edges(b_attack, output, 180);
    draw_position(default_pos, output);
    output.writeToFile("../defaultposition.png");

    //REQUIRE(average_degree(b_support) == average_degree(w_support));
    //REQUIRE(average_degree(b_attack) == average_degree(w_attack));
    //REQUIRE(average_degree(w_position) == average_degree(b_position));

    REQUIRE(weaklyconnected(b_support).size() == weaklyconnected(w_support).size());
    REQUIRE(weaklyconnected(b_position).size() == weaklyconnected(w_position).size());

    // REQUIRE(eulerian(b_support, weaklyconnected(b_support)) == eulerian(w_support, weaklyconnected(w_support)));
    // REQUIRE(eulerian(b_position) == eulerian(w_position));

    REQUIRE(numCycles(b_support) == numCycles(w_support));
    REQUIRE(numCycles(w_position) == numCycles(b_position));
    

    


}