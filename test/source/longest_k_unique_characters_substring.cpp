/**
 * @file longest_k_unique_characters_substring.cpp
 * @brief
 * @version 0.1
 * @date 2023-08-29
 *
 *
 */
#include <doctest/doctest.h>
#include <longest_k_unique_characters_substring/longest_k_unique_characters_substring.h>

TEST_CASE("longest_k_unique_characters_substring")
{
    std::string s = "aabacbebebe";
    int k = 3;
    int expected = 7;
    int actual = longest_k_substr(s, k);
    CHECK(expected == actual);

    s = "aaaa";
    k = 2;
    expected = -1;
    actual = longest_k_substr(s, k);
    CHECK(expected == actual);

    s = "aabbcc";
    k = 1;
    expected = 2;
    actual = longest_k_substr(s, k);
    CHECK(expected == actual);
}