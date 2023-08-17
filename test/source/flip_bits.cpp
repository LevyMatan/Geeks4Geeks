#include <doctest/doctest.h>
#include <flip_bits/flip_bits.h>

TEST_CASE("Flip Bits")
{
    uint32_t test_case1[5] = {1, 0, 0, 1, 0};
    uint32_t expected_result1 = 4;
    CHECK(max_ones(test_case1, 5) == expected_result1);

    uint32_t test_case2[5] = {1, 1, 1, 1, 1};
    uint32_t expected_result2 = 5;
    CHECK(max_ones(test_case2, 5) == expected_result2);

    uint32_t test_case3[5] = {0, 0, 0, 0, 0};
    uint32_t expected_result3 = 5;
    CHECK(max_ones(test_case3, 5) == expected_result3);

    uint32_t test_case4[7] = {1, 0, 0, 1, 0, 0, 1};
    uint32_t expected_result4 = 6;
    CHECK(max_ones(test_case4, 7) == expected_result4);
}
