/**
* @file catalan_number.cpp
* @brief
* @version 0.1
* @date 2023-08-17
*
*
*/
#include <doctest/doctest.h>
#include <catalan_number/catalan_number.h>

TEST_CASE("Catalan Number Recursive Test")
{
    int n = 5;
    int res = find_catalan_recursive(n);
    CHECK(res == 42);

    n = 10;
    res = find_catalan_recursive(n);
    CHECK(res == 16796);

    n = 4;
    res = find_catalan_recursive(n);
    CHECK(res == 14);

    n = 15;
    res = find_catalan_recursive(n);
    CHECK(res == 9694845);

}

TEST_CASE("Catalan Number")
{
    int n = 5;
    int res = find_catalan(n);
    CHECK(res == 42);

    n = 10;
    res = find_catalan(n);
    CHECK(res == 16796);

    n = 4;
    res = find_catalan(n);
    CHECK(res == 14);

    n = 15;
    res = find_catalan(n);
    CHECK(res == 9694845);

}