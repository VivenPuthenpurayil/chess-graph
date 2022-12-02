#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "graph.h"
#include "position.h"
#include "graph_generator.h"

using namespace std;

TEST_CASE("test GraphGenerator::default")
{   
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::list<Position::Move> moves = {Position::Move("d1e1")}; // Queen supporting the king
    Position p = Position(fen, moves, 0); // Position with one move
	Graph g = generateSupport(p);

    REQUIRE(g.num_edges() == 0);
    
}

TEST_CASE("test GraphGenerator::position from file") 
{
    std::ifstream file("../tests/output.txt");
    std::string line;
	std::getline(file, line);

	std::vector<std::string> data;
    SplitString(line, ',', data);

	Position pos(data);

}