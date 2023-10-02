/**
 * @file excel_column_name.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-02
 *
 *
 */
#include <excel_column_name/excel_column_name.h>

#include <algorithm>

/**
 * @brief Get the excel column name from column number
 *
 * @param n
 * @return std::string
 */
std::string get_excel_column_name(long long int n)
{
    std::string column_name = "";
    const long long int NUM_OF_LETTERS = 'Z' - 'A' + 1;
    while (n > 0)
    {
        n--;
        column_name += 'A' + n % NUM_OF_LETTERS;
        n /= NUM_OF_LETTERS;
    }
    std::reverse(column_name.begin(), column_name.end());
    return column_name;
}

/**
 * @brief Get the excel column number from column name
 *
 * @param column_name
 * @return long long int
 */
long long int get_excel_column_number(std::string column_name)
{
    const long long int NUM_OF_LETTERS = 'Z' - 'A' + 1;
    long long int column_number = 0;
    long long int power = 1;
    std::reverse(column_name.begin(), column_name.end());
    for (char c : column_name)
    {
        column_number += (c - 'A' + 1) * power;
        power *= NUM_OF_LETTERS;
    }
    return column_number;
}