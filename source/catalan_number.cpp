/**
 * @file catalan_number.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-17
 *
 *
 */
#include <catalan_number/catalan_number.h>

/**
 * @brief find the catalan number of n
 * This solution is based on the recursive formula of catalan number
 * @param n
 * @return int
 */
int find_catalan_recursive(int n)
{
    if (n <= 1) return 1;

    int res = 0;
    for (int i = 0; i < n; i++)
        res += find_catalan_recursive(i) * find_catalan_recursive(n - i - 1);

    return res % 1000000007;
}

/**
 * @brief find the catalan number of n
 * This solution is based on the formula of catalan number
 * @param n
 * @return int
 */
int find_catalan(int n)
{
    long long int* a_catalan = new long long int[n + 1];
    a_catalan[0] = a_catalan[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        a_catalan[i] = 0;
        for (int j = 0; j < i; j++)
            a_catalan[i]
                = (a_catalan[i] + (a_catalan[j] * a_catalan[i - j - 1]) % 1000000007) % 1000000007;
    }

    int res = (int)a_catalan[n];  // It is allowed to explicitly cast to int because the result is
                                  // guaranteed to fit in 32 bit integer after the modulo operation
    delete[] a_catalan;
    return res;
}