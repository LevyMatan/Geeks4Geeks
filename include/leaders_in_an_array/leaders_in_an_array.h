#pragma once
/**
 * @file leaders_in_an_array.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief Given an array A of positive integers. Your task is to find the leaders in the array. An
 * element of array is leader if it is greater than or equal to all the elements to its right side.
 * The rightmost element is always a leader.
 *
 * Example 1:
 *
 * Input:
 * n = 6
 * A[] = {16,17,4,3,5,2}
 * Output: 17 5 2
 * Explanation: The first leader is 17
 * as it is greater than all the elements
 * to its right.  Similarly, the next
 * leader is 5. The right most element
 * is always a leader so it is also
 * included.
 * Example 2:
 *
 * Input:
 * n = 5
 * A[] = {1,2,3,4,0}
 * Output: 4 0
 * Explanation: 0 is the rightmost element
 * and 4 is the only element which is greater
 * than all the elements to its right.
 * @version 0.1
 * @date 2023-08-19
 *
 *
 */

#include <vector>

/**
 * @brief Givan an array of positive integers, returns the leaders in the array.
 *        An element of array is leader if it is greater than or equal to all the elements to its right side.
 *
 * @param a Array of positive integers
 * @param n Number of elements in the array
 * @return std::vector<int>
 */
std::vector<int> leaders(int a[], int n);
