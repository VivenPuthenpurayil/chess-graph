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
	REQUIRE(pos.legal_moves.size() == 76);
	REQUIRE(pos.num_pieces == 32);

}

TEST_CASE("test Position::fromFile")
{
	std::ifstream file("../tests/data/preprocessed.txt");
    std::string line;
	std::getline(file, line);

	std::vector<std::string> data;
    SplitString(line, ',', data);

	file.close();

	Position pos(data);
	REQUIRE(pos.num_pieces == 28);
	Position::Piece N = pos.board[pos.toIndex("g5")];
	REQUIRE((N.type == Position::Piece::BISHOP && N.color == LIGHT));

	Position::Piece q = pos.board[pos.toIndex("d5")];

	REQUIRE((q.type == Position::Piece::QUEEN && q.color == DARK));
}
