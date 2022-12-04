#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph_algorithms.h"
#include "graph.h"
#include "utils.h"

using namespace std;

TEST_CASE("test Tarjans::empty")
{
    Graph g1(4);
    REQUIRE(num_scc(tarjans(g1)) == 4);

    Graph g2(0);
    REQUIRE(num_scc(tarjans(g2)) == 0);

    Graph g3(100);
    REQUIRE(num_scc(tarjans(g3)) == 100);
}

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

    REQUIRE(tarjans(g) == std::vector<int>{0, 0, 0, 2, 2, 5, 5, 5});

}

TEST_CASE("test Tarjans::hard 1") 
{  
    // From youtube video
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

    REQUIRE(tarjans(g) == std::vector<int>{0, 0, 0, 2, 2, 5, 5, 5, 8});

}

TEST_CASE("test Tarjans::hard 2")
{
    //From wikipedia
    Graph g(16);
    g.insertEdge(1, 0);
    g.insertEdge(0, 2);
    g.insertEdge(2, 1);
    g.insertEdge(3, 2);
    g.insertEdge(4, 3);
    g.insertEdge(2, 4);
    g.insertEdge(4, 5);
    g.insertEdge(1, 5);
    g.insertEdge(5, 6);
    g.insertEdge(5, 8);
    g.insertEdge(8, 6);
    g.insertEdge(6, 7);
    g.insertEdge(7, 8);
    g.insertEdge(7, 9);
    g.insertEdge(8, 9);
    g.insertEdge(5, 10);
    g.insertEdge(10, 11);
    g.insertEdge(11, 10);
    g.insertEdge(13, 10);
    g.insertEdge(4, 14);
    g.insertEdge(3, 15);
    g.insertEdge(15, 14);
    g.insertEdge(13, 12);
    g.insertEdge(14, 13);
    g.insertEdge(13, 15);
    g.insertEdge(12, 15);


    std::vector<int> lowlink = tarjans(g);
    int max = max_size_scc(lowlink);
    int num = num_scc(lowlink);

    REQUIRE(max == 5);
    REQUIRE(num == 6);

}
TEST_CASE("test Tarjans::harder")
{
    Graph g(9);
    g.insertEdge(0, 4);
    g.insertEdge(4, 0);
    g.insertEdge(0, 2);
    g.insertEdge(2, 0);
    g.insertEdge(2, 3);
    g.insertEdge(3, 1);
    g.insertEdge(1, 3);
    g.insertEdge(5, 4); 
    g.insertEdge(4, 3); 
    g.insertEdge(5, 1);
    g.insertEdge(6, 1);
    g.insertEdge(5, 6);
    g.insertEdge(6, 7);
    g.insertEdge(7, 5);
    g.insertEdge(8, 8);
    g.insertEdge(8, 6);
    g.insertEdge(8, 7);

    REQUIRE(tarjans(g) == std::vector<int>{0, 2, 0, 2, 0, 5, 5, 5, 8});
}
// Example for how to retrieve useful data from our lowlink list.
TEST_CASE("test Tarjans::parse lowlink")
{
    int s = 0; 
    int num = 0;
    float average_size_scc = 0;
    int max = 0;

    Graph g(9);

    // Build our graph (same as test Tarjans::harder)
    g.insertEdge(0, 4); 
    g.insertEdge(4, 0); 
    g.insertEdge(0, 2);
    g.insertEdge(2, 0);
    g.insertEdge(2, 3);
    g.insertEdge(3, 1);
    g.insertEdge(1, 3);
    g.insertEdge(5, 4); 
    g.insertEdge(4, 3); 
    g.insertEdge(5, 1);
    g.insertEdge(6, 1);
    g.insertEdge(5, 6);
    g.insertEdge(6, 7);
    g.insertEdge(7, 5);
    g.insertEdge(8, 8);
    g.insertEdge(8, 6);
    g.insertEdge(8, 7);

    std::vector<int> lowlink = tarjans(g);

    max = max_size_scc(lowlink);
    num = num_scc(lowlink);

    s = (int) lowlink.size();

    average_size_scc = (float) s / num;

    REQUIRE(average_size_scc > 1);
    REQUIRE(num == 4);
    REQUIRE(max == 3);
}

TEST_CASE("test Tarjans::parse max lowlink"){
    std::vector<int> ll{0, 0, 0, 2, 2, 1, 3, 5, 5, 6, 6, 6, 6, 6, 9, 10};
    int i = num_large_scc(ll, 0);
    int k = num_large_scc(ll, 1);
    int j = num_large_scc(ll, 2);

    REQUIRE(i == 8);
    REQUIRE(k == 4);
    REQUIRE(j == 2);

}

TEST_CASE("test Tarjans::purge small ll") {
    std::vector<int> ll{0, 0, 0, 2, 2, 1, 3, 5, 5, 6, 6, 6, 6, 6, 9, 10};
    ll = purge_small_ll(ll, 1);
    REQUIRE(ll == std::vector<int>{0, 0, 0, 2, 2, -1, -1, 5, 5, 6, 6, 6, 6, 6, -1, -1});
    ll = purge_small_ll(ll, 2);
    REQUIRE(ll == std::vector<int>{0, 0, 0, -1, -1, -1, -1, -1, -1, 6, 6, 6, 6, 6, -1, -1});

}