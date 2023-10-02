/**
 * @file number_of_distinct_subsequences.cpp
 * @brief
 * @version 0.1
 * @date 2023-10-02
 *
 *
 */
#include <doctest/doctest.h>
#include <number_of_distinct_subsequences/number_of_distinct_subsequences.h>

TEST_CASE("number_of_distinct_subsequences")
{
    CHECK(distinct_subsequences("gfg") == 7);
    CHECK(distinct_subsequences("ggg") == 4);
    CHECK(distinct_subsequences("abc") == 8);
    // "", "a", "b", "c", "ab", "bc", "abc", "bca", "cab"
}