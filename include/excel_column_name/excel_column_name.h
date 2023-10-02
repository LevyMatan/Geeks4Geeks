#pragma once
/**
 * @file excel_column_name.h
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-02
 *
 *
 */
#include <string>

/**
 * @brief Get the excel column name from column number
 * Given a positive integer, return its corresponding column title as appear in an Excel sheet.
 * Excel columns has a pattern like A, B, C, … ,Z, AA, AB, AC,…. ,AZ, BA, BB, … ZZ, AAA, AAB …..
 * etc. In other words, column 1 is named as “A”, column 2 as “B”, column 27 as “AA” and so on.
 *
 * @example 1:
 *
 * Input:
 * N = 28
 * Output: AB
 * Explanation: 1 to 26 are A to Z.
 * Then, 27 is AA and 28 = AB.
 *
 * @example 2:
 *
 * Input:
 * N = 13
 * Output: M
 * Explanation: M is the 13th character of
 * alphabet.
 * Your Task:
 * You don't need to read input or print anything. Your task is to complete the function colName()
 * which takes the column number N as input and returns the column name represented as a string.
 * Expected Time Complexity: O(LogN).
 * Expected Auxiliary Space: O(1).
 *
 * Constraints:
 * 1 <= N <= 1018
 * @param n Column number
 * @return std::string
 */
std::string get_excel_column_name(long long int n);

/**
 * @brief Get the excel column number from column name
 *
 * @param column_name
 * @return long long int
 */
long long int get_excel_column_number(std::string column_name);
