#pragma once
/**
 * @file maximum_sum_combination.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-09-25
 *
 *
 */

#include <vector>

/**
 * @brief Given two integer array A and B of size N each.
 * A sum combination is made by adding one element from array A and another element of array B.
 * Return the maximum K valid sum combinations from all the possible sum combinations.
 *
 */
std::vector<int> max_sum_combination(int N, int K, std::vector<int> &A, std::vector<int> &B);
