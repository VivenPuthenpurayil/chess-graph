#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph_algorithms.h"
#include "graph.h"
#include "utils.h"

using namespace std;

TEST_CASE("test Brandes::empty")
{
    Graph g1(4);
    std::map<int, int> check;
    for (int i =0; i < 4; i++) {
        check[i] = 0;
    }
    REQUIRE((brandes(g1)) == check);

    Graph g2(0);
    std::map<int, int> check2;
    for (int i =0; i < 0; i++) {
        check2[i] = 0;
    }
    REQUIRE((brandes(g2)) == check2);

    std::map<int, int> check3;
    for (int i =0; i < 100; i++) {
        check3[i] = 0;
    }

    Graph g3(100);
    REQUIRE((brandes(g3)) == check3);



}

TEST_CASE("test Brandes::easy")
{
    Graph g(3);
    g.insertEdge(0, 1);
    g.insertEdge(1, 2);

    std::map<int, int> check;
    check[0] = 0;
    check[1] = 2;
    check[2] = 0;
    REQUIRE(brandes(g) == check);

}

TEST_CASE("test Brandes::easy 2") 
{  
     Graph g(9);
    g.insertEdge(0, 1);
    g.insertEdge(1, 2);


    g.insertEdge(3, 4);
    g.insertEdge(4, 5);

    g.insertEdge(6, 7);
    g.insertEdge(7, 8);
    std::map<int, int> check;
    check[0] = 0;
    check[1] = 2;
    check[2] = 0;
    check[3] = 0;
    check[4] = 2;
    check[5] = 0;
    check[6] = 0;
    check[7] = 2;
    check[8] = 0;

    REQUIRE(brandes(g) == check);


    

}

TEST_CASE("test Brandes::hard 1") 
{  
    
    Graph g(7);
    g.insertEdge(0, 1);
    g.insertEdge(0, 2);


    g.insertEdge(1, 2);


    g.insertEdge(3, 2);
    g.insertEdge(3, 4);

    g.insertEdge(4, 5);
    g.insertEdge(4, 6);
    
    g.insertEdge(5, 6);
    std::map<int, int> check;
    check[0] = 0;
    check[1] = 0;
    check[2] = 16;
    check[3] = 18;
    check[4] = 16;
    check[5] = 0;
    check[6] = 0;

    REQUIRE(brandes(g) == check);
    // std::cout << "________________________________________________" << std::endl;

    // std::map<int, int> t = brandes(g);
    // for (auto e : t) {
    //     std::cout <<"Node: " <<  e.first << " has centrality of: " << e.second << std::endl;
    // }
    
    // std::cout << "________________________________________________" << std::endl;


}
TEST_CASE("test Brandes::hard 2") 
{  
    
    Graph g(6);
    g.insertEdge(0, 1);
    g.insertEdge(0, 4);

    g.insertEdge(1, 2);
    g.insertEdge(1, 3);

    g.insertEdge(2, 3);
    g.insertEdge(2, 5);

    g.insertEdge(4, 5);





    std::map<int, int> check;
    check[0] = 2;
    check[1] = 4;
    check[2] = 4;
    check[3] = 0;
    check[4] = 2;
    check[5] = 2;

    REQUIRE(brandes(g) == check);
    // std::cout << "________________________________________________" << std::endl;

    // std::map<int, int> t = brandes(g);
    // for (auto e : t) {
    //     std::cout <<"Node: " <<  e.first << " has centrality of: " << e.second << std::endl;
    // }
    
    // std::cout << "________________________________________________" << std::endl;


}

TEST_CASE("test Brandes::hard 3") 
{  
    
    Graph g(10);
    g.insertEdge(0, 1);
    g.insertEdge(0, 3);

    g.insertEdge(5, 0);
    g.insertEdge(1, 3);

    g.insertEdge(2, 8);
    g.insertEdge(2, 5);

    g.insertEdge(6, 7);
    g.insertEdge(7, 4);
    g.insertEdge(0, 9);




    std::map<int, int> check;
    check[0] = 22;
    check[1] = 0;
    check[2] = 10;
    check[3] = 0;
    check[4] = 0;
    check[5] = 16;
    check[6] = 0;
    check[7] = 2;
    check[8] = 0;
    check[9] = 0;

    REQUIRE(brandes(g) == check);
    // std::cout << "________________________________________________" << std::endl;

    // std::map<int, int> t = brandes(g);
    // for (auto e : t) {
    //     std::cout <<"Node: " <<  e.first << " has centrality of: " << e.second << std::endl;
    // }
    
    // std::cout << "________________________________________________" << std::endl;


}


TEST_CASE("test Brandes::hard 4") 
{  
    
    Graph g(8);
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 0, 1);

    g.insertEdge(3, 4, 1);
    g.insertEdge(3, 5, 1);
    g.insertEdge(3, 6, 1);
    g.insertEdge(3, 7, 1);




    std::map<int, int> check;
    check[0] = 0;
    check[1] = 0;
    check[2] = 0;
    check[3] = 12;
    check[4] = 0;
    check[5] = 0;
    check[6] = 0;
    check[7] = 0;


    REQUIRE(brandes(g) == check);
    // std::cout << "________________________________________________" << std::endl;

    // std::map<int, int> t = brandes(g);
    // for (auto e : t) {
    //     std::cout <<"Node: " <<  e.first << " has centrality of: " << e.second << std::endl;
    // }
    
    // std::cout << "________________________________________________" << std::endl;


}