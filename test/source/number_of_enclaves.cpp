/**
 * @file number_of_enclaves.cpp
 * @brief
 * @version 0.1
 * @date 2023-09-28
 *
 *
 */
#include <doctest/doctest.h>
#include <number_of_enclaves/number_of_enclaves.h>

TEST_CASE("number_of_enclaves")
{
    vector<vector<int>> grid = {{0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
    int result = number_of_enclaves(grid);
    CHECK(result == 3);

    grid = {{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};
    result = number_of_enclaves(grid);
    CHECK(result == 0);

    grid = {{0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}};
    result = number_of_enclaves(grid);
    CHECK(result == 0);

    grid = {{0, 0, 0, 0}, {1, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 1}};
    result = number_of_enclaves(grid);
    CHECK(result == 2);
}