/**
 * @file maximum_sum_combination.cpp
 * @brief
 * @version 0.1
 * @date 2023-09-25
 *
 *
 */
#include <doctest/doctest.h>
#include <maximum_sum_combination/maximum_sum_combination.h>

TEST_CASE("maximum_sum_combination")
{
    std::vector<int> a = {1, 4, 2, 3};
    std::vector<int> b = {2, 5, 1, 6};
    int N = 4;
    int K = 4;
    std::vector<int> expected = {10, 9, 9, 8};
    std::vector<int> actual = max_sum_combination(N, K, a, b);
    CHECK(actual == expected);

    a = {1, 2, 3};
    b = {2, 5, 1};
    N = 3;
    K = 2;
    expected = {8, 7};
    actual = max_sum_combination(N, K, a, b);
    CHECK(actual == expected);

    N = 17;
    a = {371, 349, 552, 343, 331, 721, 46, 572, 512, 469, 890, 608, 917, 719, 830, 104, 159};
    b = {681, 150, 595, 597, 209, 778, 666, 965, 203, 658, 273, 404, 389, 898, 847, 253, 959};
    // a_sorted = {917, 890, 830, 721, 719, 608, 572, 552, 512, 469, 371, 349, 343, 331, 159, 104,
    // 46} b_sorted = {965, 959, 898, 847, 778, 681, 666, 658, 597, 595, 404, 389, 273, 253, 209,
    // 203, 150}
    K = 6;
    // expected = {1882 1876 1855 1849 1815 1795}
    expected = {1882, 1876, 1855, 1849, 1815, 1795};
    actual = max_sum_combination(N, K, a, b);
    CHECK(actual == expected);
}