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
    std::list<Position::Move> moves = {Position::Move("d1e1"), Position::Move("a3a5")}; // Queen supporting the king, useless move
    Position p = Position(fen, moves, 0); // Position with one move
	Graph g = generateSupport(p);

    REQUIRE(g.num_edges() == 1);
    
}

TEST_CASE("test GraphGenerator::position from file") 
{
    std::ifstream file("../tests/data/preprocessed.txt");
    std::string line;
	std::getline(file, line);

	std::vector<std::string> data;
    SplitString(line, ',', data);

	Position p(data);
    Graph g = generateSupport(p);

}