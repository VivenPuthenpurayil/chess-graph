#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph_algorithms.h"
#include "graph.h"
#include "utils.h"

using namespace std;

TEST_CASE("test eulerian::empty")
{
    Graph g1(4);

    std::vector<std::vector<int>> components = weaklyconnected(g1);

    std::vector<std::list<int>> adj =  makeEulerianAdj(g1, components[0]);

    REQUIRE(eulerian(g1, adj, components) == std::vector<std::vector<int>>{{ 0 }, { 1 }, { 2 }, { 3 }});
}

TEST_CASE("test eulerian1D::easy")
{
    Graph g(5);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(1, 4, 1);
    g.insertEdge(2, 3, 1);
    g.insertEdge(3, 0, 1);
    g.insertEdge(3, 1, 1);
    g.insertEdge(4, 3, 1);

    std::vector<std::vector<int>> components = weaklyconnected(g);

    std::vector<std::list<int>> adj =  makeEulerianAdj(g, components[0]);

	REQUIRE(eulerian(g, adj, components) == std::vector<std::vector<int>>{{ 0, 1, 4, 3, 1, 2, 3, 0 }});

}

TEST_CASE("test eulerian1D::hard")
{
    Graph g(6);
    g.insertEdge(0, 1, 1);
    g.insertEdge(0, 2, 1);

    g.insertEdge(1, 4, 1);
    g.insertEdge(1, 0, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(1, 3, 1);

    g.insertEdge(2, 1, 1);
    g.insertEdge(2, 0, 1);
    g.insertEdge(2, 3, 1);
    g.insertEdge(2, 5, 1);

    g.insertEdge(3, 1, 1);
    g.insertEdge(3, 2, 1);
    g.insertEdge(3, 4, 1);
    g.insertEdge(3, 5, 1);

    g.insertEdge(4, 1, 1);
    g.insertEdge(4, 3, 1);
    g.insertEdge(4, 5, 1);

    g.insertEdge(5, 2, 1);
    g.insertEdge(5, 3, 1);
    g.insertEdge(5, 4, 1);


    std::vector<std::vector<int>> components = weaklyconnected(g);

    std::vector<std::list<int>> adj =  makeEulerianAdj(g, components[0]);
    
    REQUIRE(eulerian(g, adj, components) == std::vector<std::vector<int>>{{ 0, 2, 5, 4, 5, 3, 5, 2, 3, 4, 3, 2, 1, 4, 1, 3, 1, 2, 0, 1, 0 }});

}
