/**
* @file number_of_occurrences.cpp
* @brief
* @version 0.1
* @date 2023-08-20
*
*
*/
#include <doctest/doctest.h>
#include <number_of_occurrences/number_of_occurrences.h>

TEST_CASE("Count number of occurrences")
{
    int arr[] = {1, 2, 2, 2, 2, 3, 4, 7, 8, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 2;
    CHECK(count_linear(arr, n, x) == 4);
    CHECK(count(arr, n, x) == 4);
    x = 8;
    CHECK(count_linear(arr, n, x) == 2);
    CHECK(count(arr, n, x) == 2);
    x = 1;
    CHECK(count_linear(arr, n, x) == 1);
    CHECK(count(arr, n, x) == 1);
    x = 7;
    CHECK(count_linear(arr, n, x) == 1);
    CHECK(count(arr, n, x) == 1);
    x = 3;
    CHECK(count_linear(arr, n, x) == 1);
    CHECK(count(arr, n, x) == 1);
    x = 4;
    CHECK(count_linear(arr, n, x) == 1);
    CHECK(count(arr, n, x) == 1);
    x = 5;
    CHECK(count_linear(arr, n, x) == 0);
    CHECK(count(arr, n, x) == 0);
    x = 6;
    CHECK(count_linear(arr, n, x) == 0);
    CHECK(count(arr, n, x) == 0);
}