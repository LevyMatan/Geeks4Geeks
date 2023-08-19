/**
 * @file subarray_with_given_sum.cpp
 * @brief
 * @version 0.1
 * @date 2023-08-19
 *
 *
 */
#include <doctest/doctest.h>
#include <subarray_with_given_sum/subarray_with_given_sum.h>

TEST_CASE("subarray_with_given_sum")
{
    std::vector<int> arr = {1, 2, 3, 7, 5};
    int n = (int)arr.size();
    long long s = 12;
    CHECK(subarraySum(arr, n, s) == std::vector<int>({2, 4}));

    arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    n = (int)arr.size();
    s = 15;
    CHECK(subarraySum(arr, n, s) == std::vector<int>({1, 5}));

    arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    n = (int)arr.size();
    s = 55;
    CHECK(subarraySum(arr, n, s) == std::vector<int>({1, 10}));

    arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    n = (int)arr.size();
    s = 100;
    CHECK(subarraySum(arr, n, s) == std::vector<int>({-1}));

    arr = {1, 2, 3, 4, 5, 0, 0, 0, 0, 0};
    n = (int)arr.size();
    s = 15;
    CHECK(subarraySum(arr, n, s) == std::vector<int>({1, 5}));

    arr = {1, 2, 3, 4, 5, 0, 0, 0, 0, 0};
    n = (int)arr.size();
    s = 100;
    CHECK(subarraySum(arr, n, s) == std::vector<int>({-1}));

    arr = {1, 2, 3, 4, 5, 0, 0, 0, 0, 0};
    n = (int)arr.size();
    s = 0;
    CHECK(subarraySum(arr, n, s) == std::vector<int>({6, 6}));

    arr = {1, 2, 3, 4, 5, 0, 0, 0, 0, 0};
    n = (int)arr.size();
    s = 1;
    CHECK(subarraySum(arr, n, s) == std::vector<int>({1, 1}));
}