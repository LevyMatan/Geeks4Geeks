#include <maximum_sub_array/maximum_sub_array.h>
#include <doctest/doctest.h>

#include <vector>

TEST_CASE("Maximum Subarray")
{
    using namespace maximum_sub_array;

    int test_case1[6] = {3, -4, -3, 1, 1, 1};
    std::vector<int> expected1({1, 1, 1});
    int test_case2[6] = {3, -4, -3, 1, 0, 1};
    std::vector<int> expected2({3});
    int test_case3[6] = {3, 4, 3, 1, 1, 1};
    std::vector<int> expected3({3, 4, 3, 1, 1, 1});

    CHECK(findSubarray(test_case1, 6) == expected1);
    CHECK(findSubarray(test_case2, 6) == expected2);
    CHECK(findSubarray(test_case3, 6) == expected3);
}
