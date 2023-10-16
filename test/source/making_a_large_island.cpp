/**
 * @file making_a_large_island.cpp
 * @brief
 * @version 0.1
 * @date 2023-10-16
 *
 *
 */
#include <doctest/doctest.h>
#include <making_a_large_island/making_a_large_island.h>

TEST_CASE("Making a Large Island: toy example")
{
    vector<vector<int>> grid = {{1, 0}, {0, 1}};
    int result = largest_island(grid);
    CHECK(result == 3);

    grid = {{1, 1}, {1, 0}};
    result = largest_island(grid);
    CHECK(result == 4);

    grid = {{1, 1}, {1, 1}};
    result = largest_island(grid);
    CHECK(result == 4);

    grid = {{1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 1, 1, 1}, {0, 0, 1, 1, 1}};
    result = largest_island(grid);
    CHECK(result == 11);

    grid = {{0, 0}, {0, 0}};
    result = largest_island(grid);
    CHECK(result == 1);
}