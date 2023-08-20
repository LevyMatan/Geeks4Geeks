/**
 * @file leaders_in_an_array.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-19
 *
 *
 */
#include <leaders_in_an_array/leaders_in_an_array.h>

#include <algorithm>

/**
 * @brief Givan an array of positive integers, returns the leaders in the array.
 *        An element of array is leader if it is greater than or equal to all the elements to its
 * right side.
 *
 * @param a Array of positive integers
 * @param n Number of elements in the array
 * @return std::vector<int>
 */
std::vector<int> leaders(int a[], int n)
{
    std::vector<int> leaders;
    int max = a[n - 1];
    leaders.push_back(max);
    for (int i = n - 2; i >= 0; i--)
    {
        if (a[i] >= max)
        {
            max = a[i];
            leaders.push_back(max);
        }
    }
    std::reverse(leaders.begin(), leaders.end());
    return leaders;
}