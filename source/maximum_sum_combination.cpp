/**
* @file maximum_sum_combination.cpp
* @author Matan Levy (levymatanlevy@gmail.com)
* @brief Given two integer array A and B of size N each.
A sum combination is made by adding one element from array A and another element of array B.
Return the maximum K valid sum combinations from all the possible sum combinations.

Note : Output array must be sorted in non-increasing order.
* @version 0.1
* @date 2023-09-25
*
*
*/
#include <maximum_sum_combination/maximum_sum_combination.h>

#include <algorithm>
#include <queue>
#include <utility>

/**
 *
 */
static bool compare(int a, int b)
{
    return a > b;  // Compare in reverse order
}

/**
 * @brief Given two integer array A and B of size N each.
 * A sum combination is made by adding one element from array A and another element of array B.
 * Return the maximum K valid sum combinations from all the possible sum combinations.
 *
 */
std::vector<int> max_sum_combination(int N, int K, std::vector<int> &A, std::vector<int> &B)
{
    std::sort(A.begin(), A.end(), compare);
    std::sort(B.begin(), B.end(), compare);
    std::vector<int> res(K, 0);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::less<std::pair<int, int>>>
        pq;

    for (int i = 0; i < N; i++)
    {
        pq.push(std::pair<int, int>(A[i] + B[0], 0));
    }

    int k = 0;

    while (k < K)
    {
        std::pair<int, int> p = pq.top();
        pq.pop();

        int sum = p.first;
        int j = p.second;

        res[k] = sum;

        if (j < N - 1)
        {
            pq.push(std::pair<int, int>(sum - B[j] + B[j + 1], j + 1));
        }

        k++;
    }

    return res;
}