#pragma once
/**
* @file find_four_sum.h
* @author Matan Levy (levymatanlevy@gmail.com)
* @brief Given an array A of integers and another number K. Find all the unique quadruple from the
given array that sums up to K.

Also note that all the quadruples which you return should be internally sorted, ie for any quadruple
[q1, q2, q3, q4] the following should follow: q1 <= q2 <= q3 <= q4.

Example 1:

Input:
N = 5, K = 3
A[] = {0,0,2,1,1}
Output: 0 0 1 2
Explanation: Sum of 0, 0, 1, 2 is equal
to K.
Example 2:

Input:
N = 7, K = 23
A[] = {10,2,3,4,5,7,8}
Output: 2 3 8 10
        2 4 7 10
        3 5 7 8
Explanation: Sum of 2, 3, 8, 10 = 23,
sum of 2, 4, 7, 10 = 23 and sum of 3,
5, 7, 8 = 23.
Your Task:
You don't need to read input or print anything. Your task is to complete the function fourSum()
which takes the array arr[] and the integer k as its input and returns an array containing all the
quadruples in a lexicographical manner. In the output each quadruple is separate by $. The printing
is done by the driver's code.

Expected Time Complexity: O(N3).
Expected Auxiliary Space: O(N2).
* @version 0.1
* @date 2023-09-25
*
*
*/

#include <vector>

/**
 * @brief
 *
 * @param arr
 * @param k
 * @return std::vector<std::vector<int> >
 */
std::vector<std::vector<int> > find_four_sum(std::vector<int> &arr, int k);
