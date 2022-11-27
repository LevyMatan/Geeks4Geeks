/**
 * @file maximum_sub_array.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <maximum_sub_array/maximum_sub_array.h>
#include <vector>

/**
 * @brief Find out the maximum sub-array of non negative numbers from an array.
 *
 *        The sub-array should be contiguous i.e., a sub-array created by choosing the second and fourth element and skipping the third element is invalid.
 *
 *        Maximum sub-array is defined in terms of the sum of the elements in the sub-array. Sub-array A is greater than sub-array B if sum(A) > sum(B).
 *
 *        Example:
 *        a = [1, 2, 5, -7, 2, 3]
 *        The two sub-arrays are [1, 2, 5] [2, 3].
 *        The answer is [1, 2, 5] as its sum is larger than [2, 3]
 *
 *        NOTE: If there is a tie, then compare with segment's length and return segment which has maximum length.
 *        If there is still a tie, then return the segment with minimum starting index.
 *        If no such subarray is present return "-1"
 *
 *        Example 1:
 *
 *        Input:
 *        n = 3
 *        a[] = {1, 2, 3}
 *        Output: 1 2 3
 *        Explanation: In the given array every
 *        element is non-negative.
 *        Example 2:
 *
 *        Input:
 *        n = 2
 *        a[] = {-1, 2}
 *        Output: 2
 *        Explanation: The only subarray [2] is
 *        the answer.
 *
 *
 *        Your Task:
 *        Complete the function findSubarray() which takes the array a and the size of the array, n, as input parameters and returns an array representing the answer. If there is no subarray return an array of length 1 containing -1 only. You don't to print answer or take inputs.
 *
 *        Expected Time Complexity: O(N)
 *        Expected Auxiliary Space: O(1)
 *
 *        Constraints:
 *        1 ≤ N ≤ 105
 *        -105 ≤ A[i] ≤ 105
 * URL:
 * https://practice.geeksforgeeks.org/problems/maximum-sub-array5443/1
 */
namespace maximum_sub_array {

    /**
     * @brief
     *
     * @param a
     * @param n
     * @return std::vector<int>
     */
    std::vector<int> findSubarray(int a[], int n) {
        std::vector<int> res;
        int starting_idx_sub_array = 0;
        int ending_idx_sub_array = n;
        int sub_array_len = 0;
        int sum = 0;

        int temp_start_idx = 0;
        int temp_end_idx = 0;
        int temp_len = 0;
        int temp_sum = 0;
        for(int i = 0; i < n; i++)
        {
            const int num = a[i];

            if(num >= 0)
            {
                temp_sum += num;
            }
            else
            {
                temp_len = i - temp_start_idx;

                if( (temp_sum > sum)                                                         ||
                    ((temp_sum == sum) && (temp_len > sub_array_len))                        ||
                    ((temp_len == sub_array_len) && (temp_start_idx < starting_idx_sub_array)) )
                {
                    starting_idx_sub_array = temp_start_idx;
                    ending_idx_sub_array = i;
                    sub_array_len = ending_idx_sub_array - starting_idx_sub_array;
                    sum = temp_sum;
                }

                temp_start_idx = i;
                temp_end_idx = i;
                temp_sum = 0;
                temp_len = 0;
            }
        }
        if(temp_sum > 0)
        {
            temp_end_idx = n;
            temp_len = temp_end_idx - temp_start_idx;
        }
        if( (temp_sum > sum)                                                         ||
            ((temp_sum == sum) && (temp_len > sub_array_len))                        ||
            ((temp_len == sub_array_len) && (temp_start_idx < starting_idx_sub_array)) )
        {
            starting_idx_sub_array = temp_start_idx;
            ending_idx_sub_array = temp_end_idx;
            sub_array_len = ending_idx_sub_array - starting_idx_sub_array;
            sum = temp_sum;
        }
        for(int i = starting_idx_sub_array; i < ending_idx_sub_array; i++)
        {
            if(a[i] >= 0)
            {
                res.push_back(a[i]);
            }
        }
        if(res.size() == 0)
        {
            res.push_back(-1);
        }

        return res;

    }
}  // namespace maximum_sub_array