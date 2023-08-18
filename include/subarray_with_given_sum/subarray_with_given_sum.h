#pragma once
/**
* @file subarray_with_given_sum.h
* @author Matan Levy (levymatanlevy@gmail.com)
* @brief
* @version 0.1
* @date 2023-08-19
*
*
*/
#include <vector>

/**
 * @brief Given an unsorted array A of size N that contains only positive integers, find a continuous
 * sub-array that adds to a given number S and return the left and right index(1-based indexing) of
 * that subarray.
 *
 * @param n
 * @param s
 * @return vector<int>
 */
std::vector<int> subarraySum(std::vector<int>arr, int n, long long s);