#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "graph.h"
#include "position.h"
#include "graph_generator.h"
#include "graph_algorithms.h"

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