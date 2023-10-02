#pragma once
/**
 * @file number_of_distinct_subsequences.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-02
 *
 *
 */

#include <string>

/**
 * @brief Given a string consisting of lower case English alphabets, the task is to find the number
 * of distinct subsequences of the string.
 *
 * @example Input: s = "gfg"
 *         Output: 7
 *        Explanation: The seven distinct subsequences are "", "g", "f", "gf", "fg", "gg" and "gfg"
 *
 * @example Input: s = "ggg"
 *        Output: 4
 *       Explanation: The four distinct subsequences are "", "g", "gg" and "ggg"
 *
 * @param s String consisting of lower case English alphabets
 * @return int Number of distinct subsequences of the string
 */
int distinct_subsequences(std::string s);
