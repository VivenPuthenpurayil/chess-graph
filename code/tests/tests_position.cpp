#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Position.h>

using namespace std;


TEST_CASE("firstTest")
{
	Position pos;
	Position::Piece p = pos.board[pos.toIndex("a2")];
	REQUIRE((p.type == Position::Piece::PAWN && p.color == LIGHT));
	REQUIRE(true);
}