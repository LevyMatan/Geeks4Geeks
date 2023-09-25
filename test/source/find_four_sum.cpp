/**
 * @file find_four_sum.cpp
 * @brief
 * @version 0.1
 * @date 2023-09-25
 *
 *
 */
#include <doctest/doctest.h>
#include <find_four_sum/find_four_sum.h>

TEST_CASE("find_four_sum: 1")
{
    std::vector<int> arr = {0, 0, 2, 1, 1};
    int k = 3;
    std::vector<std::vector<int> > result = find_four_sum(arr, k);
    std::vector<std::vector<int> > expected = {{0, 0, 1, 2}};
    CHECK(result == expected);

    arr = {10, 2, 3, 4, 5, 7, 8};
    k = 23;
    result = find_four_sum(arr, k);
    expected = {{2, 3, 8, 10}, {2, 4, 7, 10}, {3, 5, 7, 8}};
    CHECK(result == expected);
}