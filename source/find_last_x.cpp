/**
 * @file find_last_x.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-09-25
 *
 *
 */
#include <find_last_x/find_last_x.h>

/**
 * @brief Naive solution
 *
 * @param arr
 * @param n
 * @param x
 * @return std::vector<int>
 */
std::vector<int> find_last_x::find_naive(int arr[], int n, int x)
{
    int first = -1;
    int last = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            if (first == -1)
            {
                first = i;
            }
            last = i;
        }
    }
    std::vector<int> result;
    result.push_back(first);
    result.push_back(last);
    return result;
}

/**
 * @brief find the first and last occurrences of an element x in the given array.
 * Note: If the number x is not found in the array then return both the indices as -1.
 * Example 1:
 *      Input:
 *          n=9, x=5
 *          arr[] = { 1, 3, 5, 5, 5, 5, 67, 123, 125 }
 *      Output:
 *          {2, 5}
 *      Explanation:
 *      First occurrence of 5 is at index 2 and last occurrence of 5 is at index 5.
 *
 * Time Complexity: O(logN)
 * @param arr sorted array
 * @param n number of elements in arr
 * @param x target element
 * @return std::vector<int> the first and last occurrences of an element x in the given array.
 */
std::vector<int> find_last_x::find(int arr[], int n, int x)
{
    int first = -1;
    int last = -1;
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == x)
        {
            first = mid;
            high = mid - 1;
        }
        else if (arr[mid] > x)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == x)
        {
            last = mid;
            low = mid + 1;
        }
        else if (arr[mid] > x)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    std::vector<int> result;
    result.push_back(first);
    result.push_back(last);
    return result;
}