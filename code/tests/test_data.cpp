#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include "utils.h"
#include <vector>

TEST_CASE("test Analysis::Linear Regression basic") {
    std::vector<float> x{0, 1, 2, 3, 4, 5};
    std::vector<float> y{.5, 1, 1.5, 3, 4.5, 4.7};
    float r2 = LinearRegression(x, y);
    std::cout << r2 << "\n";
    REQUIRE(r2 > .9);
}
