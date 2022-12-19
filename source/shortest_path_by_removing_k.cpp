/**
 * @file shretest_path_remove_k.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <shortest_path_by_removing_k/shortest_path_by_removing_k.h>
#include <utils/debug.h>

#include <queue>
#include <vector>

/**
 * @brief Find out the maximum sub-array of non negative numbers from an array.
 *
 *        The sub-array should be contiguous i.e., a sub-array created by choosing the second and
 * fourth element and skipping the third element is invalid.
 *
 *        Maximum sub-array is defined in terms of the sum of the elements in the sub-array.
 * Sub-array A is greater than sub-array B if sum(A) > sum(B).
 *
 *        Example:
 *        a = [1, 2, 5, -7, 2, 3]
 *        The two sub-arrays are [1, 2, 5] [2, 3].
 *        The answer is [1, 2, 5] as its sum is larger than [2, 3]
 *
 *        NOTE: If there is a tie, then compare with segment's length and return segment which has
 * maximum length. If there is still a tie, then return the segment with minimum starting index. If
 * no such subarray is present return "-1"
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
 *        Complete the function findSubarray() which takes the array a and the size of the array, n,
 * as input parameters and returns an array representing the answer. If there is no subarray return
 * an array of length 1 containing -1 only. You don't to print answer or take inputs.
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
namespace shortest_path_by_removing_k
{

    typedef struct queue_element_s
    {
        int dist;
        int row;
        int col;
        int k;
    } queue_element_t;

    // static __unused__ int  shortestPathRec(std::vector<std::vector<int>> &mat, int row, int col,
    // int k, std::vector<std::vector<std::vector<bool>>> &visited,
    // std::vector<std::vector<std::vector<int>>> &memo)
    // {
    //     int m = mat.size();
    //     int n = mat[0].size();

    //     int MIN_DIST_POSSIBLE = (m-1-row) + (n-1-col);
    //     if ((m-1 == row) && (n-1 == col))
    //     {
    //         visited[k][row][col] = true;
    //         memo[k][row][col] = 0;
    //         return 0;
    //     }
    //     if(visited[k][row][col])
    //     {
    //         return memo[k][row][col];
    //     }
    //     int backup = mat[row][col];
    //     mat[row][col] = 2;
    //     bool memomize = true;

    //     debug_print("=======================================\n");
    //     debug_print("=======================================\n");
    //     debug_print("row = %d, col = %d, k = %d\n", row, col, k);
    //     debug_print("=======================================\n");

    //     for(int i = 0; i < m; i++)
    //     {
    //         for (int j = 0; j < n; j++)
    //         {
    //             debug_print("%d ", mat[i][j]);
    //         }
    //         debug_print("\n");
    //     }
    //     debug_print("=======================================\n");
    //     debug_print("=======================================\n");

    //     int min_dist = INT_MAX;
    //     int dist_right = -1;
    //     int dist_down = -1;
    //     int dist_left = -1;
    //     int dist_up = -1;

    //     if (col + 1 < n)
    //     {
    //         if (mat[row][col+1] == 1)
    //         {
    //             if(k > 0)
    //             {
    //                 dist_right = shortestPathRec(mat, row, col+1, k-1, visited, memo);
    //             }
    //         }
    //         else if (mat[row][col+1] == 0)
    //         {
    //             dist_right = shortestPathRec(mat, row, col+1, k, visited, memo);
    //         }
    //         else{
    //             memomize = false;
    //         }
    //     }
    //     debug_print("dist_right is: %d\n", dist_right);
    //     if((dist_right != -1) && (dist_right < min_dist))
    //     {
    //         min_dist = dist_right+1;
    //     }
    //     if(MIN_DIST_POSSIBLE == min_dist)
    //     {
    //         goto exit_func;
    //     }
    //     if (row + 1 < m)
    //     {
    //         if (mat[row+1][col] == 1)
    //         {
    //             if(k > 0)
    //             {
    //                 dist_down = shortestPathRec(mat, row+1, col, k-1, visited, memo);
    //             }
    //         }
    //         else if (mat[row+1][col] == 0)
    //         {
    //             dist_down = shortestPathRec(mat, row+1, col, k, visited, memo);
    //         }
    //         else
    //         {
    //             memomize = false;
    //         }
    //     }
    //     if((dist_down != -1) && (dist_down < min_dist))
    //     {
    //         min_dist = dist_down+1;
    //     }
    //     if(MIN_DIST_POSSIBLE == min_dist)
    //     {
    //         goto exit_func;
    //     }
    //     if ((col - 1) >= 0)
    //     {
    //         if (mat[row][col-1] == 1)
    //         {
    //             if(k > 0)
    //             {
    //                 dist_left = shortestPathRec(mat, row, col-1, k-1, visited, memo);
    //             }
    //         }
    //         else if (mat[row][col-1] == 0)
    //         {
    //             dist_left = shortestPathRec(mat, row, col-1, k, visited, memo);
    //         }
    //         else
    //         {
    //             memomize = false;
    //         }
    //     }
    //     if((dist_left != -1) && (dist_left < min_dist))
    //     {
    //         min_dist = dist_left+1;
    //     }
    //     if(MIN_DIST_POSSIBLE == min_dist)
    //     {
    //         goto exit_func;
    //     }
    //     if (row - 1 >= 0)
    //     {
    //         if (mat[row-1][col] == 1)
    //         {
    //             if(k > 0)
    //             {
    //                 dist_up = shortestPathRec(mat, row-1, col, k-1, visited, memo);
    //             }
    //         }
    //         else if (mat[row-1][col] == 0)
    //         {
    //             dist_up = shortestPathRec(mat, row-1, col, k, visited, memo);
    //         }
    //         else
    //         {
    //             memomize = false;
    //         }
    //     }
    //     if((dist_up != -1) && (dist_up < min_dist))
    //     {
    //         min_dist = dist_up+1;
    //     }

    //     exit_func:
    //     if (min_dist == INT_MAX)
    //     {
    //         min_dist = -1;
    //     }

    //     if(memomize)
    //     {
    //         visited[k][row][col] = true;
    //         memo[k][row][col] = min_dist;
    //     }

    //     if (min_dist == -1)
    //     {
    //         for(int k_idx = k-1; k_idx >= 0; k_idx--)
    //         {
    //             visited[k_idx][row][col] = true;
    //             memo[k_idx][row][col] = min_dist;
    //         }
    //     }
    //     mat[row][col] = backup;
    //     debug_print("memo[%d][%d][%d] = %d\n", k, row, col, memo[k][row][col]);
    //     return min_dist;

    // }

    int shortestPath(std::vector<std::vector<int>> mat, int n, int m, int k)
    {
        std::vector<std::vector<int>> visited(n, std::vector<int>(m, -1));
        std::queue<queue_element_t> q;
        q.push({0, 0, 0, k});

        while (!q.empty())
        {
            queue_element_t top_cell = q.front();
            q.pop();

            int dist = top_cell.dist;
            int row = top_cell.row;
            int col = top_cell.col;
            int cell_k = top_cell.k;
            if (row == n - 1 && col == m - 1)
            {
                return dist;  // reached to destination
            }

            if ((visited[row][col] != -1) && (visited[row][col] >= cell_k))
            {
                continue;  // important case
            }
            visited[row][col] = cell_k;

            if (mat[row][col])
            {
                if (cell_k > 0)
                {
                    cell_k--;
                }
                else
                {
                    continue;
                }
            }

            if (row + 1 < n)
            {
                q.push({dist + 1, row + 1, col, cell_k});
            }
            if (col + 1 < m)
            {
                q.push({dist + 1, row, col + 1, cell_k});
            }
            if (row - 1 >= 0)
            {
                q.push({dist + 1, row - 1, col, cell_k});
            }
            if (col - 1 >= 0)
            {
                q.push({dist + 1, row, col - 1, cell_k});
            }
        }

        return -1;
    }
}  // namespace shortest_path_by_removing_k