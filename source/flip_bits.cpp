/**
 * @file flip_bits.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-15-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "flip_bits/flip_bits.h"

/**
 * @brief Given an array arr[] consisting of 0’s and 1’s. A flip operation is one in which you turn
 * 1 into 0 and a 0 into 1. You have to do at most one “Flip” operation of any subarray. Formally,
 * select a range (l, r) in the array A[], such that (0 ≤ l ≤ r < n) holds and flip the elements in
 * this range to get the maximum ones in the final array. You can possibly make zero operations to
 * get the answer. Expected Time Complexity: O(N) Expected Auxiliary Space: O(1) Constraints: 1 ≤ N
 * ≤ 106 0 ≤ A[i] ≤ 1
 *
 * ### Example 1
 *
 * ```
 * Input:
 * N = 5
 * A[] = {1, 0, 0, 1, 0}
 * Output:
 * 4
 * Explanation:
 * We can perform a flip operation in the range [1,2]
 * After flip operation array is : [ 1 1 1 1 0 ]
 * Count of one's after fliping is : 4
 * ```
 *
 * ### Example 2
 *
 * ```
 * Input:
 * N = 7
 * A[] = {1, 0, 0, 1, 0, 0, 1}
 * Output:
 * 6
 * Explanation:
 * We can perform a flip operation in the range [1,5]
 * After flip operation array is : [ 1 1 1 0 1 1 1]
 * Count of one after fliping is : 6
 * ```
 * Algorithm:
 * Count the number of 0's in the array.
 *
 * @param arr
 * @param n
 * @return uint32_t
 */
uint32_t max_ones(uint32_t arr[], uint32_t n)
{
    uint32_t count = 0;
    uint32_t max_count = 0;
    uint32_t ones_count = 0;
    for (uint32_t i = 0; i < n; i++)
    {
        if (arr[i] == 0)
        {
            count++;
        }
        else
        {
            ones_count++;
            if (count > 0)
            {
                count--;
            }
        }
        if (count > max_count)
        {
            max_count = count;
        }
    }
    return max_count + ones_count;
}