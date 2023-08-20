#pragma once
/**
* @file number_of_occurrences.h
* @author Matan Levy (levymatanlevy@gmail.com)
* @brief
* @version 0.1
* @date 2023-08-20
*
*
*/

/**
 * @brief if x is present in arr[] then returns the count
 *		  of occurrences of x, otherwise returns 0.
 *          Complexity O(n)
 * 
 * @param arr - Array of integers
 * @param n  - Number of elements in the array
 * @param x - Number to count its occurrences
 * @return int - Number of occurrences of x in arr
 */
int count_linear(int arr[], int n, int x);

/**
 * @brief if x is present in arr[] then returns the count
 *		  of occurrences of x, otherwise returns 0.
 *          Complexity O(log(n))
 * 
 * @param arr - Array of integers
 * @param n  - Number of elements in the array
 * @param x - Number to count its occurrences
 * @return int - Number of occurrences of x in arr
 */
int count(int arr[], int n, int x);