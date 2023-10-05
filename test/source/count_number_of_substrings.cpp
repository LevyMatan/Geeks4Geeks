/**
 * @file count_number_of_substrings.cpp
 * @brief
 * @version 0.1
 * @date 2023-10-04
 *
 *
 */
#include <count_number_of_substrings/count_number_of_substrings.h>
#include <doctest/doctest.h>

TEST_CASE("Count Number of Substrings: Toy Examples")
{
    std::string str = "aba";
    int k = 2;
    CHECK(count_substrings(str, k) == 3);

    str = "abaaca";
    k = 1;
    CHECK(count_substrings(str, k) == 7);
}