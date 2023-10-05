/**
 * @file count_number_of_substrings.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-04
 *
 *
 */
#include <count_number_of_substrings/count_number_of_substrings.h>

#include <cstring>

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
long long int count_substrings(std::string &str, int k)
{
    int n = str.length();
    int res = 0;
    int cnt[26];

    for (int i = 0; i < n; i++)
    {
        int dist_count = 0;
        memset(cnt, 0, sizeof(cnt));

        for (int j = i; j < n; j++)
        {
            if (cnt[str[j] - 'a'] == 0)
            {
                dist_count++;
            }
            cnt[str[j] - 'a']++;

            if (dist_count == k)
            {
                res++;
            }
        }
    }
    return res;
}

// Using sliding window
long long int count_substrings_optimised(std::string &str, int k)
{
    int n = str.length();
    int res = 0;
    int cnt[26];
    int dist_count = 0;
    int window_start = 0;

    memset(cnt, 0, sizeof(cnt));

    for (int window_end = 0; window_end < n; window_end++)
    {
        if (cnt[str[window_end] - 'a'] == 0)
        {
            dist_count++;
        }
        cnt[str[window_end] - 'a']++;

        while (dist_count > k)
        {
            cnt[str[window_start] - 'a']--;
            if (cnt[str[window_start] - 'a'] == 0)
            {
                dist_count--;
            }
            window_start++;
        }
        if (dist_count == k)
        {
            res++;
        }
    }
    return res;
}