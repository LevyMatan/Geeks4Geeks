#pragma once
/**
 * @file longest_k_unique_characters_substring.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-08-29
 *
 *
 */

#include <string>

/**
 * @brief find the length of the longest substring with k unique characters in a given string
 *        Algorithm:
 *        1. Create an array of size 26 (for each letter in the alphabet).
 *           The value in each cell will be the highest index of that char.
 *        2. Create a variable called start, which will be the start of the substring.
 *           It should be initialized to 0.
 *        3. iterate over the string, and for each char:
 *          3.1. Check if this character is already in our substring by looking at the value in the
 *               array.
 *          3.2. update the value in the array of the current char to be the current index.
 *
 *
 *
 * @param s string of only lower case characters
 * @param k number of unique characters
 * @return int the length of the longest substring with k unique characters in a given string, if
 * doesnt exist return -1
 */
int longest_k_substr(std::string s, int k);