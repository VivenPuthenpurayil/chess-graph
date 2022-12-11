#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "graph.h"
#include "position.h"
#include "graph_generator.h"

#define LIGHT 1
#define DARK 0

using namespace std;

TEST_CASE("test BuildSupportGraph::default")
{   
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::list<Position::Move> moves = {Position::Move("d1e1"), Position::Move("a3a5")}; // Queen supporting the king, fake move
    Position p = Position(fen, moves, 0); // Position with one move
	Graph g = generateSupport(p, LIGHT);

    REQUIRE(g.num_edges() == 1);
    
}

TEST_CASE("test BuildSupportGraph::simple") 
{
    // Manually build the position
    std::string fen = "8/8/8/8/6P1/5P2/4P3/8 w - - 0 1";
    std::list<Position::Move> moves = {Position::Move("e2f3"), Position::Move("e2d3"), Position::Move("f3g4"), Position::Move("f3e4"), Position::Move("g4f5"), Position::Move("g4h5")};
    Position p = Position(fen, moves, 0);
    Graph g = generateSupport(p, LIGHT);

    REQUIRE(g.num_edges() == 2);

}

TEST_CASE("test BuildSupportGraph::position from file") 
{
    std::ifstream file("../tests/data/preprocessed.txt");
    std::string line;
	std::getline(file, line);

	std::vector<std::string> data;
    SplitString(line, ',', data);

    file.close();

	Position p(data);
    Graph white_support = generateSupport(p, LIGHT);
    Graph black_support = generateSupport(p, DARK);

}

