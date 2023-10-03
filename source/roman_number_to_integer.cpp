/**
 * @file roman_number_to_integer.cpp
 * @author Matan Levy (levymatanlevy@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-03
 *
 *
 */
#include <roman_number_to_integer/roman_number_to_integer.h>

#include <unordered_map>

int roman_to_decimal(std::string &str)
{
    std::unordered_map<char, int> roman_values
        = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    int res = 0;
    int str_length = (int)str.length();

    for (auto i = 0; i < str_length; i++)
    {
        int s1 = roman_values[str[i]];
        if (i + 1 < str_length)
        {
            auto s2 = roman_values[str[i + 1]];
            if (s1 >= s2)
            {
                res = res + s1;
            }
            else
            {
                res = res + s2 - s1;
                i++;
            }
        }
        else
        {
            res = res + s1;
        }
    }
    return res;
}