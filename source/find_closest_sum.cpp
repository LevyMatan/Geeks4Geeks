/**
 * @file find_closest_sum.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-09-26
 *
 *
 */
#include <find_closest_sum/find_closest_sum.h>
#include <stdlib.h>
#include <utils/debug.h>

#include <climits>

std::vector<int> printClosest(int arr[], int brr[], int n, int m, int x)
{
    int min_dist = INT_MAX;

    int left = 0;
    int right = m - 1;

    std::vector<int> result;

    while (left < n && right >= 0)
    {
        int dist = abs(arr[left] + brr[right] - x);
        debug_print("left: %d, arr[left]: %d, right: %d, brr[right]: %d, dist: %d\n", left,
                    arr[left], right, brr[right], dist);
        if (dist < min_dist)
        {
            min_dist = dist;
            if (result.empty())
            {
                result.push_back(arr[left]);
                result.push_back(brr[right]);
            }
            result[0] = arr[left];
            result[1] = brr[right];
        }
        if (arr[left] + brr[right] < x)
        {
            left++;
        }
        else
        {
            right--;
        }
    }

    return result;
}