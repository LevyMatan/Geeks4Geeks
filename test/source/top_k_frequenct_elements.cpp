/**
 * @file top_k_frequenct_elements.cpp
 * @brief
 * @version 0.1
 * @date 2023-11-05
 *
 *
 */
#include <doctest/doctest.h>
#include <top_k_frequenct_elements/top_k_frequenct_elements.h>

TEST_CASE("top_k_frequenct_elements")
{
    std::vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;
    std::vector<int> res = top_k_frequenct_elements::topK(nums, k);
    CHECK(res[0] == 1);
    CHECK(res[1] == 2);

    nums = {1, 1, 2, 2, 3, 3, 3, 4};
    k = 2;
    res = top_k_frequenct_elements::topK(nums, k);
    CHECK(res[0] == 3);
    CHECK(res[1] == 2);
}