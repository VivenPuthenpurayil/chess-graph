#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "position.h"
#include "utils.h"

using namespace std;

TEST_CASE("test Position::default")
{
	Position pos;
	Position::Piece p = pos.board[pos.toIndex("a2")];
	REQUIRE((p.type == Position::Piece::PAWN && p.color == LIGHT));
	REQUIRE(pos.legal_moves.size() == 0);
	REQUIRE(pos.num_pieces == 32);

}

TEST_CASE("test Position::fromFile")
{
	std::ifstream file("../tests/output.txt");
    std::string line;
	std::getline(file, line);

	std::vector<std::string> data;
    SplitString(line, ',', data);

	Position pos(data);
	REQUIRE(pos.num_pieces == 26);
	Position::Piece N = pos.board[pos.toIndex("e4")];
	REQUIRE((N.type == Position::Piece::KNIGHT && N.color == LIGHT));

	Position::Piece q = pos.board[pos.toIndex("g6")];

	REQUIRE((q.type == Position::Piece::QUEEN && q.color == DARK));
	REQUIRE(pos.legal_moves.size() == 32);
	REQUIRE(pos.evaluation > 130);

}
