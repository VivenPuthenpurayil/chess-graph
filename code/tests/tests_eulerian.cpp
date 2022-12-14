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

    REQUIRE(eulerian(g1, components) == std::vector<std::vector<int>>{{ 0 }, { 1 }, { 2 }, { 3 }});
}

TEST_CASE("test eulerian::no eularian cycle")
{
    Graph g(8);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 0, 1);

    g.insertEdge(3, 4, 1);
    g.insertEdge(3, 5, 1);
    g.insertEdge(3, 6, 1);
    g.insertEdge(3, 7, 1);

    std::vector<std::vector<int>> components = weaklyconnected(g);

    REQUIRE(components == std::vector<std::vector<int>>{{ 0, 1, 2 }, { 3, 4, 5, 6, 7 }});

    std::vector<std::vector<int>> eul = eulerian(g, components);

	REQUIRE(eul == std::vector<std::vector<int>>{{ 0, 1, 2, 0 }, {  }});

    REQUIRE(numCycles(g) == 1);

}

TEST_CASE("test eulerian::2-D both not a eularian cycle")
{
    Graph g(9);
    g.insertEdge(0, 1, 1);
    g.insertEdge(0, 2, 1);
    g.insertEdge(0, 3, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(1, 3, 1);
    g.insertEdge(2, 3, 1);

    g.insertEdge(4, 5, 1);
    g.insertEdge(5, 6, 1);
    g.insertEdge(6, 7, 1);
    g.insertEdge(7, 4, 1);
    g.insertEdge(4, 8, 1);
    g.insertEdge(6, 8, 1);

    std::vector<std::vector<int>> components = weaklyconnected(g);

    REQUIRE(components == std::vector<std::vector<int>>{{ 0, 1, 2, 3 }, { 4, 5, 6, 7, 8}});

    std::vector<std::vector<int>> eul = eulerian(g, components);

	REQUIRE(eul == std::vector<std::vector<int>>{{  }, {  }});

    REQUIRE(numCycles(g) == 0);

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

	REQUIRE(eulerian(g, components) == std::vector<std::vector<int>>{{ 0, 1, 4, 3, 1, 2, 3, 0 }});

    REQUIRE(numCycles(g) == 1);

}

TEST_CASE("test eulerian::medium2")
{
    Graph g(5);
    g.insertEdge(0, 1, 1);
    g.insertEdge(0, 4, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 0, 1);
    g.insertEdge(2, 3, 1);
    g.insertEdge(3, 2, 1);
    g.insertEdge(3, 0, 1);
    g.insertEdge(4, 3, 1);

    std::vector<std::vector<int>> components = weaklyconnected(g);

	REQUIRE(eulerian(g, components) == std::vector<std::vector<int>>{{ 0, 4, 3, 2, 3, 0, 1, 2, 0 }});

    REQUIRE(numCycles(g) == 1);

}

TEST_CASE("test eulerian::2 connected components first")
{
    Graph g(8);
    g.insertEdge(0, 1, 1);
    g.insertEdge(0, 4, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 0, 1);
    g.insertEdge(2, 3, 1);
    g.insertEdge(3, 2, 1);
    g.insertEdge(3, 0, 1);
    g.insertEdge(4, 3, 1);

    g.insertEdge(5, 6, 1);
    g.insertEdge(6, 7, 1);
    g.insertEdge(7, 5, 1);

    std::vector<std::vector<int>> components = weaklyconnected(g);

    REQUIRE(components == std::vector<std::vector<int>>{{ 0, 1, 2, 3, 4 }, { 5, 6, 7 }});

    std::vector<std::vector<int>> eul = eulerian(g, components);

	REQUIRE(eul == std::vector<std::vector<int>>{{ 0, 4, 3, 2, 3, 0, 1, 2, 0 }, {5, 6, 7, 5}});

    REQUIRE(numCycles(g) == 2);

}

TEST_CASE("test eulerian::2 connected components second")
{
    Graph g(8);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 0, 1);

    g.insertEdge(3, 4, 1);
    g.insertEdge(4, 5, 1);
    g.insertEdge(4, 7, 1);
    g.insertEdge(5, 6, 1);
    g.insertEdge(6, 3, 1);
    g.insertEdge(6, 4, 1);
    g.insertEdge(7, 6, 1);

    std::vector<std::vector<int>> components = weaklyconnected(g);

    REQUIRE(components == std::vector<std::vector<int>>{{ 0, 1, 2 }, { 3, 4, 5, 6, 7 }});

    std::vector<std::vector<int>> eul = eulerian(g, components);

	REQUIRE(eul == std::vector<std::vector<int>>{{ 0, 1, 2, 0 }, { 3, 4, 7, 6, 4, 5, 6, 3 }});

    REQUIRE(numCycles(g) == 2);

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

    REQUIRE(components == std::vector<std::vector<int>>{{ 0, 1, 2, 3, 4, 5 }});
    
    REQUIRE(eulerian(g, components) == std::vector<std::vector<int>>{{ 0, 2, 5, 4, 5, 3, 5, 2, 3, 4, 3, 2, 1, 4, 1, 3, 1, 2, 0, 1, 0 }});

    REQUIRE(numCycles(g) == 1);
}


TEST_CASE("test eulerian::3D connected components second")
{
    Graph g(12);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 0, 1);

    g.insertEdge(3, 4, 1);
    g.insertEdge(4, 5, 1);
    g.insertEdge(4, 7, 1);
    g.insertEdge(5, 6, 1);
    g.insertEdge(6, 3, 1);
    g.insertEdge(6, 4, 1);
    g.insertEdge(7, 6, 1);

    g.insertEdge(8, 9, 1);
    g.insertEdge(9, 10, 1);
    g.insertEdge(10, 11, 1);
    g.insertEdge(11, 8, 1);

    std::vector<std::vector<int>> components = weaklyconnected(g);

    REQUIRE(components == std::vector<std::vector<int>>{{ 0, 1, 2 }, { 3, 4, 5, 6, 7 }, {8, 9, 10, 11}});

    std::vector<std::vector<int>> eul = eulerian(g, components);

	REQUIRE(eul == std::vector<std::vector<int>>{{ 0, 1, 2, 0 }, { 3, 4, 7, 6, 4, 5, 6, 3 },  {8, 9, 10, 11, 8}});

    REQUIRE(numCycles(g) == 3);

}
