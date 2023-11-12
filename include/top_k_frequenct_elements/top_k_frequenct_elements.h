#pragma once
/**
* @file top_k_frequenct_elements.h
* @author Matan Levy (levymatanlevy@gmail.com)
* @brief Given a non-empty array nums[] of integers of length N, find the top k elements which have
the highest frequency in the array. If two numbers have same frequencies, then the larger number
should be given more preference.

Example 1:

Input:
N = 6
nums = {1,1,1,2,2,3}
k = 2
Output: {1, 2}
Example 2:

Input:
N = 8
nums = {1,1,2,2,3,3,3,4}
k = 2
Output: {3, 2}
Explanation: Elements 1 and 2 have the
same frequency ie. 2. Therefore, in this
case, the answer includes the element 2
as 2 > 1.
User Task:
You don't have to read or print anything. You will have to complete the function topK() that takes
an array nums[] and integer k as input and returns a list of top k most frequent elements. If any
two elements have same frequencies, then give more preference to the larger elemet.

Expected Time Complexity : O(NlogN)
Expected Auxilliary Space : O(N)

Constraints:
1 <= N <= 105
1<= nums[i] <=105
1 <= k <= N
* @version 0.1
* @date 2023-11-05
*
*
*/

#include <vector>

namespace top_k_frequenct_elements
{

    using std::vector;

    /**
     * @brief Given a non empty array nums[] of integers of length N, find the top k elements which
     * have the highest frequency in the array. If two numbers have same frequencies, then the
     * larger number should be given more preference.
     *
     * @param nums
     * @param k
     * @return vector<int>
     */
    vector<int> topK(vector<int>& nums, int k);

}  // namespace top_k_frequenct_elements
