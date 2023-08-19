/**
* @file leaders_in_an_array.cpp
* @brief
* @version 0.1
* @date 2023-08-19
*
*
*/
#include <doctest/doctest.h>
#include <leaders_in_an_array/leaders_in_an_array.h>

TEST_CASE("leaders_in_an_array")
{
    int a[] = {16, 17, 4, 3, 5, 2};
    int n = sizeof(a) / sizeof(a[0]);
    std::vector<int> leaders_arr = leaders(a, n);
    CHECK_EQ(leaders_arr.size(), 3);
    CHECK_EQ(leaders_arr[0], 17);
    CHECK_EQ(leaders_arr[1], 5);
    CHECK_EQ(leaders_arr[2], 2);

    int b[] = {1, 2, 3, 4, 0};
    n = sizeof(b) / sizeof(b[0]);
    leaders_arr = leaders(b, n);
    CHECK_EQ(leaders_arr.size(), 2);
    CHECK_EQ(leaders_arr[0], 4);
    CHECK_EQ(leaders_arr[1], 0);

    int c[] = {7, 4, 5, 7, 3};
    n = sizeof(c) / sizeof(c[0]);
    leaders_arr = leaders(c, n);
    CHECK_EQ(leaders_arr.size(), 3);
    CHECK_EQ(leaders_arr[0], 7);
    CHECK_EQ(leaders_arr[1], 7);
    CHECK_EQ(leaders_arr[2], 3);

    int d[] = {1, 2, 3, 4, 5};
    n = sizeof(d) / sizeof(d[0]);
    leaders_arr = leaders(d, n);
    CHECK_EQ(leaders_arr.size(), 1);
    CHECK_EQ(leaders_arr[0], 5);

    int e[] = {5, 4, 3, 2, 1};
    n = sizeof(e) / sizeof(e[0]);
    leaders_arr = leaders(e, n);
    CHECK_EQ(leaders_arr.size(), 5);
    CHECK_EQ(leaders_arr[0], 5);
    CHECK_EQ(leaders_arr[1], 4);
    CHECK_EQ(leaders_arr[2], 3);
    CHECK_EQ(leaders_arr[3], 2);
    CHECK_EQ(leaders_arr[4], 1);

    int f[] = {1, 1, 1, 1, 1};
    n = sizeof(f) / sizeof(f[0]);
    leaders_arr = leaders(f, n);
    CHECK_EQ(leaders_arr.size(), 5);
    CHECK_EQ(leaders_arr[0], 1);
    CHECK_EQ(leaders_arr[1], 1);
    CHECK_EQ(leaders_arr[2], 1);
    CHECK_EQ(leaders_arr[3], 1);
    CHECK_EQ(leaders_arr[4], 1);

    int g[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    n = sizeof(g) / sizeof(g[0]);
    leaders_arr = leaders(g, n);
    CHECK_EQ(leaders_arr.size(), 5);
    CHECK_EQ(leaders_arr[0], 5);
    CHECK_EQ(leaders_arr[1], 4);
    CHECK_EQ(leaders_arr[2], 3);
    CHECK_EQ(leaders_arr[3], 2);
    CHECK_EQ(leaders_arr[4], 1);


}