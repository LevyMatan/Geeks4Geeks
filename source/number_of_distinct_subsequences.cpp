/**
 * @file number_of_distinct_subsequences.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-02
 *
 *
 */
#include <number_of_distinct_subsequences/number_of_distinct_subsequences.h>

#include <vector>

int distinct_subsequences(std::string s)
{
    int n = s.length();
    std::vector<int> dp(n + 1);
    dp[0] = 1;
    int last[26];
    for (int i = 0; i < 26; i++)
    {
        last[i] = -1;
    }
    for (int i = 1; i <= n; i++)
    {
        dp[i] = (2 * dp[i - 1]) % 1000000007;
        if (last[s[i - 1] - 'a'] != -1)
        {
            dp[i] = (dp[i] - dp[last[s[i - 1] - 'a']] + 1000000007) % 1000000007;
        }
        last[s[i - 1] - 'a'] = i - 1;
    }
    return dp[n];
}