#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph_algorithms.h"
#include "graph.h"
#include "utils.h"

using namespace std;

TEST_CASE("test Tarjans::easy")
{
    Graph g(3);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 0, 1);

	REQUIRE(tarjans(g) == std::vector<int>{0, 0, 0});

}

TEST_CASE("test Tarjans::medium") 
{  
    Graph g(8);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 0, 1);
    g.insertEdge(0, 2, 1);
    g.insertEdge(2, 0, 1);
    g.insertEdge(2, 3, 1);
    g.insertEdge(3, 4, 1);
    g.insertEdge(4, 3, 1);
    g.insertEdge(5, 1, 1);
    g.insertEdge(1, 3, 1);
    g.insertEdge(5, 4, 1);
    g.insertEdge(6, 4, 1);
    g.insertEdge(5, 6, 1);
    g.insertEdge(6, 7, 1);
    g.insertEdge(7, 5, 1);

    // Ignore 9th vertex for now

    REQUIRE(tarjans(g) == std::vector<int>{0, 0, 0, 3, 3, 5, 5, 5});

}

TEST_CASE("test Tarjans::hard") 
{  
    Graph g(9);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 0, 1);
    g.insertEdge(0, 2, 1);
    g.insertEdge(2, 0, 1);
    g.insertEdge(2, 3, 1);
    g.insertEdge(3, 4, 1);
    g.insertEdge(4, 3, 1);
    g.insertEdge(5, 1, 1);
    g.insertEdge(1, 3, 1);
    g.insertEdge(5, 4, 1);
    g.insertEdge(6, 4, 1);
    g.insertEdge(5, 6, 1);
    g.insertEdge(6, 7, 1);
    g.insertEdge(7, 5, 1);

    g.insertEdge(8, 8, 1);
    g.insertEdge(8, 6, 1);
    g.insertEdge(8, 7, 1);

    REQUIRE(tarjans(g) == std::vector<int>{0, 0, 0, 3, 3, 5, 5, 5, 8});

}