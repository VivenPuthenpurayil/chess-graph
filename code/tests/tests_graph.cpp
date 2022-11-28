#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "graph.h"
#include "utils.h"

using namespace std;

TEST_CASE("test Graph::default")
{
	Graph g(3);

    REQUIRE(g.edgeExists(0, 1) == false);
    for (int i = 0; i < 3; i++) {
        REQUIRE(g.degree(i) == 0);
        REQUIRE(g.neighbors(i).empty() == true);
    }
    REQUIRE(g.num_edges() == 0);
    
}

TEST_CASE("test Graph::insert & remove")
{
    Graph g(3);

    g.insertEdge(1, 2, 2);
    REQUIRE(g.num_edges() == 1);
    REQUIRE(g.edgeExists(1, 2));
    REQUIRE(!g.edgeExists(2, 1));
    REQUIRE(g.weight(1,2) == 2);

    g.removeEdge(1, 2);
    REQUIRE(g.num_edges() == 0);
    REQUIRE(!g.edgeExists(1, 2));
    REQUIRE(!g.edgeExists(2, 1));

    g.insertEdge(1, 2, 5);
    g.insertEdge(2, 1, 1);
    REQUIRE(g.num_edges() == 2);
    REQUIRE(g.edgeExists(1, 2));
    REQUIRE(g.edgeExists(2, 1));
    REQUIRE(g.weight(1,2) == 5);

    
}

TEST_CASE("test Graph::degree")
{
	Graph g(3);

    g.insertEdge(1, 2, 2);
    g.insertEdge(0, 2, 10);
    REQUIRE(g.in_degree(2) == 2);
    REQUIRE(g.out_degree(2) == 0);
    
    g.insertEdge(2, 1, 6);
    REQUIRE(g.out_degree(2) == 1);
    REQUIRE(g.degree(2) == 3);

}

TEST_CASE("test Graph::neighbors")
{
	Graph g(5);
    std::list<int> n;

    g.insertEdge(1, 2, 8);
    g.insertEdge(0, 2, -4);

    n = g.in_neighbors(2);
    n.sort();

    REQUIRE(g.in_neighbors(2) == std::list<int>{0, 1});
    REQUIRE(g.out_neighbors(2).empty() == true);
    
    g.insertEdge(2, 1, 4);

    REQUIRE(g.out_neighbors(2) == std::list<int>{1});

    g.insertEdge(2, 3, -2);
    g.insertEdge(4, 2, -3);
    g.insertEdge(2, 0, -5);

    n = g.neighbors(2);
    n.sort();
    REQUIRE(n == std::list<int>{0, 1, 3, 4});

}

TEST_CASE("test graph::out_neighbor_self") 
{
    Graph g(1);
    g.insertEdge(0, 0, 1);
    std::list<int> n = g.out_neighbors(0);
    REQUIRE(n == std::list<int>{0});
}

TEST_CASE("test Graph::weight")
{
    Graph g(3);

    g.insertEdge(1, 2, 2);
    REQUIRE(g.weight(1,2) == 2);

    g.removeEdge(1, 2);

    g.insertEdge(1, 2, 5);
    g.insertEdge(2, 1, -1);
    REQUIRE(g.weight(1,2) == 5);
    REQUIRE(g.weight(2,1) == -1);

    
}