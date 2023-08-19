/**
 * @file subarray_with_given_sum.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief Given an unsorted array A of size N that contains only positive integers, find a
 * continuous sub-array that adds to a given number S and return the left and right index(1-based
 * indexing) of that subarray.
 *
 * In case of multiple subarrays, return the subarray indexes which come first on moving from left
 * to right.
 *
 * Note:- You have to return an ArrayList consisting of two elements left and right. In case no such
 * subarray exists return an array consisting of element -1.
 *
 * Example 1:
 *
 * Input:
 * N = 5, S = 12
 * A[] = {1,2,3,7,5}
 * Output: 2 4
 * Explanation: The sum of elements
 * from 2nd position to 4th position
 * is 12.
 * Example 2:
 *
 * Input:
 * N = 10, S = 15
 * A[] = {1,2,3,4,5,6,7,8,9,10}
 * Output: 1 5
 * Explanation: The sum of elements
 * from 1st position to 5th position
 * is 15.
 * @version 0.1
 * @date 2023-08-19
 *
 *
 */
#include <subarray_with_given_sum/subarray_with_given_sum.h>

/**
 * @brief Given an unsorted array A of size N that contains only positive integers, find a
 * continuous sub-array that adds to a given number S and return the left and right index(1-based
 * indexing) of that subarray.
 *
 * @param n
 * @param s
 * @return vector<int>
 */
std::vector<int> subarraySum(std::vector<int> arr, int n, long long s)
{
    int start = 0, end = 0;
    long long sum = 0;
    while (end < n)
    {
        sum += arr[end];
        if (sum == s)
        {
            return {start + 1, end + 1};
        }
        else if (sum > s)
        {
            while (sum > s)
            {
                sum -= arr[start];
                start++;
            }
            if (sum == s)
            {
                // check if start is greater than end
                // It handle the edge case when the required sum is 0.
                // Hence we do not want to stop searching for the subarray.
                if (start <= end)
                {
                    return {start + 1, end + 1};
                }
            }
        }
        end++;
    }
    return {-1};
}