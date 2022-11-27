#include <vector>

/**
 * @brief Shreyansh and his bits
 *
 *        Shreyansh has an integer N.
 *        He is really curious about the binary representation of integers.
 *        He sees that any given integer has a number of set bits.
 *        Now he wants to find out that how many positive integers,
 *        strictly less than N, have the same number of set bits as N.
 *        He is a little weak in maths. Help him find the number of integers.
 *        Note : Since N takes large values, brute force won't work.
 *
 *        Example 1:
 *
 *        Input:
 *        N = 8
 *        Output: 3
 *        Explanation:
 *        Binary representation of 8 : 1000
 *        So the integers less than 8 with
 *        same number of set bits are : 4, 2, 1
 *        Hence, the result is 3.
 *
 *
 *        Example 2:
 *
 *        Input:
 *        N = 4
 *        Output: 2
 *        Explanation:
 *        Binary representation of 4 : 100
 *        So the integers less than 4 with
 *        same number of set bits are : 2, 1
 *        So, The result is 2.
 *
 *        Expected Time Complexity: O(log(n))
 *        Expected Auxiliary Space: O(log(n)*log(n))
 *
 *
 *        Constraints :
 *        1 <= N <= 10^12
 *
 * URL: https://practice.geeksforgeeks.org/problems/shreyansh-and-his-bits1420/1
 *
 */
namespace shenyrash_and_his_bits
{

    /**
     * @brief count the number of numbers strictly lower than x
     *        which has the exact same number of bit set on them.
     *
     * @param x
     * @return long long
     */
    long long count(long long x)
    {
        /**
         * @brief Algorithm:
         *        Step 1: Count the number of bits in x, mark as K.
         *        Step 2: Find the Left Most Bit ON, and mark its index as N.
         *                We can generate numbers stricly lower in two manners.
         *                  Turn LMB OFF :
         *                      Compute the number of permutation of K bits in N cells.
         *                      That is exactly n choose k which we can compute before with pascal
         * triangle. Keep LMB ON : Find the next LMB wich is ON and repeat step 2.
         *
         */

        // First we need to count the number of bits in x
        // This is a O(1) operation
        long long count = 0;    /// count the number of bits SET in x.
        long long max_idx = 0;  /// Keep the Left Most Bit SET in x.
        for (long long idx = 63; idx >= 0; idx--)
        {
            if (x & (1ULL << idx))
            {
                if (idx > max_idx)
                {
                    max_idx = idx;
                }
                count++;
            }
        }

        if ((max_idx + 1) == count)
        {
            return 0;
        }

        /**
         * @brief Fill n choose k by doing "Pascal Triangle"
         *
         */
        std::vector<std::vector<long long>> n_choose_k(max_idx + 1,
                                                       std::vector<long long>(max_idx + 1, 0));
        for (long long n = 1; n < max_idx + 1; n++)
        {
            for (long long k = 0; k <= n; k++)
            {
                if (k == 0)
                {
                    n_choose_k[n][k] = 1;
                }
                else if (k == n)
                {
                    n_choose_k[n][k] = 1;
                }
                else if (k > n)
                {
                    n_choose_k[n][k] = 0;
                }
                else
                {
                    n_choose_k[n][k] = n_choose_k[n - 1][k - 1] + n_choose_k[n - 1][k];
                }
                // printf("n_choose_k[%d][%d] = %lld\n", n,k, n_choose_k[n][k]);
            }
        }

        long long count_permutations = 0;  /// count the number of numbers lower than x.
        for (long long idx = 63; idx > 0; idx--)
        {
            if (x & (1ULL << idx))
            {
                // With bit OFF
                // printf("x had bit %lld on, there are %d bits to toggle\n", idx, count);
                count_permutations += n_choose_k[idx][count];
                count--;
            }
        }

        return count_permutations;
    }
}  // namespace shenyrash_and_his_bits