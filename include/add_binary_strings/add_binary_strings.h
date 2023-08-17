#pragma once
/**
 * @file add_binary_strings.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <string>

/**
 * @brief Given two binary strings A and B consisting of only 0s and 1s.
 *        Find the resultant string after adding the two Binary Strings.
 *        Note: The input strings may contain leading zeros but the output
 *              string should not have any leading zeros.
 *
 *          Example 1:
 *
 *          Input:
 *          A = "1101", B = "111"
 *          Output: 10100
 *          Explanation:
 *           1101
 *          + 111
 *          10100
 *          Example 2:
 *
 *          Input:
 *          A = "10", B = "01"
 *          Output: 11
 *          Explanation:
 *            10
 *          + 01
 *            11
 *
 * URL: https://practice.geeksforgeeks.org/problems/add-binary-strings3805/1
 */
namespace add_binary_strings
{
    /**
     * @brief Compute the some of A and B when represented as binary strings.
     *
     * @param A string representing a binary number, only holds chars of '0's and '1's
     * @param B string representing a binary number, only holds chars of '0's and '1's
     * @return string representing the sum of A and B
     */
    std::string add_binary(std::string A, std::string B);
}  // namespace add_binary_strings
