/**
 * @file find_closest_sum.cpp
 * @brief
 * @version 0.1
 * @date 2023-09-26
 *
 *
 */
#include <doctest/doctest.h>
#include <find_closest_sum/find_closest_sum.h>

TEST_CASE("find_closest_sum")
{
    int arr[] = {1, 4, 5, 7};
    int brr[] = {10, 20, 30, 40};
    int x = 32;
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = sizeof(brr) / sizeof(brr[0]);
    std::vector<int> result = printClosest(arr, brr, n, m, x);
    CHECK(result[0] == 1);
    CHECK(result[1] == 30);
}