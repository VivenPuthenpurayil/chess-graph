#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include "utils.h"
#include <vector>


TEST_CASE("Data Clean 1")
{
	std::ifstream file("../tests/data/test.txt");
    std::string s;
    std::vector<std::string> check;
    // std::getline(file,s);


    if (file.is_open()) {
        while (file.good()) {
            std::getline(file, s);
            check.push_back(s);
            std::cout << "___________________" << std::endl; 
            std::cout << s << std::endl;
        }
    }
	REQUIRE(check.size() == 3);
    REQUIRE(check[0] == "r3kb1r/pp1bnpp1/1q2p2p/2ppP1N1/5PB1/2PP1K1P/PP1N4/R1BR4 w kq - 0 17,g5h7,g5f7,g5e6,g5e4,g4e6,g4h5,g4f5,f3e4,f3g3,f3e3,f3g2,f3f2,f3e2,d2e4,d2c4,d2b3,d2f1,d2b1,d1h1,d1g1,d1f1,d1e1,a1b1,f4f5,h3h4,d3d4,c3c4,b2b3,a2a3,b2b4,a2a4,0");
    REQUIRE(check[1] == "3q1rk1/p1p2p2/Q2pbn2/2b1p1p1/4P2p/2PP2BP/P2N1PP1/R4RK1 w - - 0 17,a6c8,a6b7,a6a7,a6d6,a6c6,a6b6,a6b5,a6a5,a6c4,a6a4,a6a3,g3e5,g3h4,g3f4,g3h2,d2c4,d2f3,d2b3,d2b1,g1h2,g1h1,f1e1,f1d1,f1c1,f1b1,a1e1,a1d1,a1c1,a1b1,d3d4,c3c4,f2f3,a2a3,f2f4,a2a4,0");
}

// TEST_CASE("Data Clean 2")
// {
// 	std::ifstream file("../tests/test2.txt");
//     std::string s;
//     std::vector<std::string> check;


//     if (file.is_open()) {
//         while (file.good()) {
//             std::getline(file, s);
//             check.push_back(s);
//             std::cout << "___________________" << std::endl; 
//     std::cout << s << std::endl;
//         }
//     }
// 	REQUIRE(check.size() == 3);
//     REQUIRE(check[0] == "r3kb1r/pp1bnpp1/1q2p2p/2ppP1N1/5PB1/2PP1K1P/PP1N4/R1BR4 w kq - 0 17,g5h7,g5f7,g5e6,g5e4,g4e6,g4h5,g4f5,f3e4,f3g3,f3e3,f3g2,f3f2,f3e2,d2e4,d2c4,d2b3,d2f1,d2b1,d1h1,d1g1,d1f1,d1e1,a1b1,f4f5,h3h4,d3d4,c3c4,b2b3,a2a3,b2b4,a2a4,0");
//     REQUIRE(check[1] == "3q1rk1/p1p2p2/Q2pbn2/2b1p1p1/4P2p/2PP2BP/P2N1PP1/R4RK1 w - - 0 17,a6c8,a6b7,a6a7,a6d6,a6c6,a6b6,a6b5,a6a5,a6c4,a6a4,a6a3,g3e5,g3h4,g3f4,g3h2,d2c4,d2f3,d2b3,d2b1,g1h2,g1h1,f1e1,f1d1,f1c1,f1b1,a1e1,a1d1,a1c1,a1b1,d3d4,c3c4,f2f3,a2a3,f2f4,a2a4,0");
// }

TEST_CASE("test Analysis::Linear Regression basic") {
    std::vector<float> x{0, 1, 2, 3, 4, 5};
    std::vector<float> y{.5, 1, 1.5, 3, 4.5, 4.7};
    float r2 = LinearRegression(x, y);
    std::cout << r2;
    REQUIRE(r2 > .9);


}
