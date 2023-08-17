/**
 * @file next_smallest_palindrome.cpp
 * @brief
 * @version 0.1
 * @date 2023-08-17
 *
 *
 */
#include <doctest/doctest.h>
#include <next_smallest_palindrome/next_smallest_palindrome.h>

TEST_CASE("next_smallest_palindrome")
{
    /**
     * Input:
        N = 11
        Num[] = {9, 4, 1, 8, 7, 9, 7, 8, 3, 2, 2}
        Output: 9 4 1 8 8 0 8 8 1 4 9
    */
    int num1[] = {9, 4, 1, 8, 7, 9, 7, 8, 3, 2, 2};
    int n = sizeof(num1) / sizeof(num1[0]);
    vector<int> result = generateNextPalindrome(num1, n);
    CHECK_EQ(result[0], 9);
    CHECK_EQ(result[1], 4);
    CHECK_EQ(result[2], 1);
    CHECK_EQ(result[3], 8);
    CHECK_EQ(result[4], 8);
    CHECK_EQ(result[5], 0);
    CHECK_EQ(result[6], 8);
    CHECK_EQ(result[7], 8);
    CHECK_EQ(result[8], 1);
    CHECK_EQ(result[9], 4);
    CHECK_EQ(result[10], 9);
    /**
     * Input:
        N = 5
        Num[] = {1, 2, 3, 4, 5}
        Output: 1 2 4 2 1
    */
    int num2[] = {1, 2, 3, 4, 5};
    n = sizeof(num2) / sizeof(num2[0]);
    result = generateNextPalindrome(num2, n);
    CHECK_EQ(result[0], 1);
    CHECK_EQ(result[1], 2);
    CHECK_EQ(result[2], 4);
    CHECK_EQ(result[3], 2);
    CHECK_EQ(result[4], 1);

    /**
     * Input:
     * N = 5
     * Num[] = {2, 3, 5, 4, 5}
     * Output: 2 3 6 3 2
     */
    int num3[] = {2, 3, 5, 4, 5};
    n = sizeof(num3) / sizeof(num3[0]);
    result = generateNextPalindrome(num3, n);
    CHECK_EQ(result[0], 2);
    CHECK_EQ(result[1], 3);
    CHECK_EQ(result[2], 6);
    CHECK_EQ(result[3], 3);
    CHECK_EQ(result[4], 2);

    /**
     * Input:
     * N = 1
     * Num[] = {1}
     */
    int num4[] = {1};
    n = sizeof(num4) / sizeof(num4[0]);
    result = generateNextPalindrome(num4, n);
    CHECK_EQ(result[0], 2);
}