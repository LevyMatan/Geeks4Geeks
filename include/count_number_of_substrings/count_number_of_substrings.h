#pragma once
/**
 * @file count_number_of_substrings.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-04
 *
 *
 */
#include <string>

/**
 * @brief Given a string of lowercase alphabets, count all possible substrings (not necessarily
distinct) that have exactly k distinct characters.

Example 1:

Input:
S = "aba", K = 2
Output:
3
Explanation:
The substrings are: "ab", "ba" and "aba".
Example 2:

Input:
S = "abaaca", K = 1
Output:
7
Explanation:
The substrings are: "a", "b", "a", "aa", "a", "c", "a".
Your Task:
You don't need to read input or print anything. Your task is to complete the function substrCount()
which takes the string S and an integer K as inputs and returns the number of substrings having
exactly K distinct characters.

Expected Time Complexity: O(|S|).
Expected Auxiliary Space: O(1).

Constraints:
1 ≤ |S| ≤ 106
1 ≤ K ≤ 26
 *
 * @param str
 * @return long long int
 */
long long int count_substrings(std::string &str, int k);