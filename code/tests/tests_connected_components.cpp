#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph_algorithms.h"
#include "graph.h"
#include "utils.h"

using namespace std;

TEST_CASE("test weakly connected components::empty")
{
    Graph g1(4);
    REQUIRE(weaklyconnected(g1) == std::vector<std::vector<int>>{{ 0 }, { 1 }, { 2 }, { 3 }});

    Graph g2(0);
    REQUIRE(weaklyconnected(g2) == std::vector<std::vector<int>>{});
}

TEST_CASE("test weakly connected components::easy")
{
    Graph g(3);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 0, 1);

	REQUIRE(weaklyconnected(g) == std::vector<std::vector<int>>{{0,1,2,}});

}
