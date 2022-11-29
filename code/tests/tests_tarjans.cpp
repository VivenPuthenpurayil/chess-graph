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

    REQUIRE(tarjans(g) == std::vector<int>{0, 0, 0, 2, 2, 5, 5, 5});

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

    REQUIRE(tarjans(g) == std::vector<int>{0, 0, 0, 2, 2, 5, 5, 5, 8});

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
    int num_scc = 0;
    float average_size_scc = 0;
    int max_size_scc = 0;

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

    std::map<int, int> sizes;
    for (int i : lowlink) {
        sizes[i]++;
    }

    int max_size = std::max_element(sizes.begin(), sizes.end(),  
    [] (const std::pair<int, int> & p1, const std::pair<int, int> & p2) {
        return p1.second < p2.second;}
    )->second;

    s = (int) lowlink.size();

    std::sort(lowlink.begin(), lowlink.end());
    auto last = std::unique(lowlink.begin(), lowlink.end());
    lowlink.resize(std::distance(lowlink.begin(), last));

    num_scc = lowlink.size();
    average_size_scc = (float) s / num_scc;

    REQUIRE(average_size_scc > 1);
    REQUIRE(num_scc == 4);
    REQUIRE(max_size == 3);


}