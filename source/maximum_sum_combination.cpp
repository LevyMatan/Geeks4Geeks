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
    int ind_a = 0;
    int ind_b = 0;
    std::vector<int> res(K, 0);
    std::vector<int> ind_a_max(N, 0);
    std::vector<int> ind_b_max(N, 0);

    for (int ind_k = 0; ind_k < K; ind_k++)
    {
        int sum = A[ind_a] + B[ind_b];
        res[ind_k] = sum;

        // What will be the next element?
        int element_a;
        int element_b;
        if (ind_a + 1 < N)
        {
            element_a = A[ind_a + 1];
            element_b = B[ind_b_max[ind_a + 1]];
        }
        else
        {
            element_a = A[ind_a];
            element_b = B[ind_b_max[ind_a] + 1];
        }
        int option_1 = element_a + element_b;

        if (ind_b + 1 < N)
        {
            element_b = B[ind_b + 1];
            element_a = A[ind_a_max[ind_b + 1]];
        }
        else
        {
            element_b = B[ind_b];
            element_a = A[ind_a_max[ind_b] + 1];
        }
        int option_2 = element_a + element_b;

        if (option_1 < option_2)
        {
            if (ind_b + 1 < N)
            {
                ind_b++;
                ind_a = ind_a_max[ind_b];
                ind_a_max[ind_b]++;
            }
            else
            {
                ind_a_max[ind_b]++;
                ind_a = ind_a_max[ind_b];
            }
        }
        else
        {
            if (ind_a + 1 < N)
            {
                ind_a++;
                ind_b = ind_b_max[ind_a];
                ind_b_max[ind_a]++;
            }
            else
            {
                ind_b_max[ind_a]++;
                ind_b = ind_b_max[ind_a];
            }
        }
    }

    return res;
}