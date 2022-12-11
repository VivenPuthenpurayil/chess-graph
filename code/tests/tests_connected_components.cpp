#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph_algorithms.h"
#include "graph.h"
#include "utils.h"

using namespace std;

TEST_CASE("test WCC::empty")
{
    Graph g1(4);
    REQUIRE(weaklyconnected(g1) == std::vector<std::vector<int>>{{ 0 }, { 1 }, { 2 }, { 3 }});

    Graph g2(0);
    REQUIRE(weaklyconnected(g2) == std::vector<std::vector<int>>{});
}

TEST_CASE("test WCC::easy 1")
{
    Graph g(3);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 0, 1);

	REQUIRE(weaklyconnected(g) == std::vector<std::vector<int>>{{0,1,2,}});

}

TEST_CASE("test WCC::easy 2")
{
    //from geeksforgeeks
    Graph g(6);
    g.insertEdge(0, 1, 1);
    g.insertEdge(0, 2, 1);
    g.insertEdge(3, 2, 1);
    g.insertEdge(3, 1, 1);
    g.insertEdge(4, 5, 1);



	REQUIRE(weaklyconnected(g) == std::vector<std::vector<int>>{{0,1,3,2,},{4,5,}});

}
TEST_CASE("test WCC::medium") 
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

    REQUIRE(weaklyconnected(g) == std::vector<std::vector<int>>{{0,1,3,2,4,5,6,7}});

}

TEST_CASE("test WCC::hard")
{
    Graph g(14);

	g.insertEdge(0, 4);
    g.insertEdge(0, 3);
    g.insertEdge(1, 2);

    g.insertEdge(1, 4);
    g.insertEdge(3, 2);
    g.insertEdge(4, 3);
    g.insertEdge(2, 4);
    g.insertEdge(5, 11);
    g.insertEdge(11, 12);
    g.insertEdge(9, 6);
    g.insertEdge(7, 6);
    g.insertEdge(6, 7);
    g.insertEdge(8, 7);
    g.insertEdge(9, 8);
    g.insertEdge(9, 10);

    REQUIRE(weaklyconnected(g) == std::vector<std::vector<int>>{{0,3,2,1,4},{5,11,12},{6,7,8,9,10},{13}});



}